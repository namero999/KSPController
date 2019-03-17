package lol.corrado;

import krpc.client.Connection;
import krpc.client.RPCException;
import krpc.client.Stream;
import krpc.client.services.KRPC;
import krpc.client.services.SpaceCenter;
import krpc.client.services.SpaceCenter.*;
import krpc.client.services.UI;
import lol.corrado.model.Telemetry;
import lol.corrado.utils.Utils;
import lombok.SneakyThrows;
import org.javatuples.Triplet;

import static java.lang.Thread.sleep;
import static krpc.client.services.UI.MessagePosition.TOP_CENTER;
import static lol.corrado.model.ControlData.sasMode;
import static lol.corrado.model.ControlData.sasOn;

public class KRPCLogic {

    private KRPC krpc;
    private UI ui;

    private SpaceCenter spaceCenter;
    byte sas = 0;
    byte mode = 0;

    @SneakyThrows
    public void start() {

        Stream<Double> apoapsis = null;
        Stream<Double> periapsis = null;
        Stream<Double> inclination = null;

        Stream<Double> altitude = null;
        Stream<Double> vSpeed = null;
        Stream<Double> hSpeed = null;

        try (Connection connection = Connection.newInstance()) {

            setupKrpc(connection);

            Vessel vessel = spaceCenter.getActiveVessel();
            Control control = setupPreFlight(vessel);

            Orbit orbit = vessel.getOrbit();
            CelestialBody body = orbit.getBody();
            Flight flight = vessel.flight(vessel.getSurfaceReferenceFrame());

            Telemetry.vesselName = Utils.toChars(vessel.getName());
            Telemetry.body = Utils.toChars(body.getName());

            // ORBITAL
            apoapsis = connection.addStream(orbit, "getApoapsisAltitude");
            periapsis = connection.addStream(orbit, "getPeriapsisAltitude");
            inclination = connection.addStream(orbit, "getInclination");

            // SURFACE
            altitude = connection.addStream(flight, "getMeanAltitude");
            vSpeed = connection.addStream(flight, "getVerticalSpeed");
            hSpeed = connection.addStream(flight, "getHorizontalSpeed");

            while (true) {

                Telemetry.apoapsisMeters = (float) (double) apoapsis.get();
                Telemetry.periapsisMeters = (float) (double) periapsis.get();
                Telemetry.inclinationDegrees = (float) (inclination.get() * 180 / Math.PI); // Math.toDegrees(inclination.get())

                Telemetry.altitude = (float) (double) altitude.get();
                Telemetry.vSpeed = (float) (double) vSpeed.get();
                Telemetry.hSpeed = (float) (double) hSpeed.get();


                if (sas != sasOn) {
                    sas = sasOn;
                    control.setSAS(sas == 1);
                    System.out.println(sasMode);
                    if (sas == 1) {
                        sleep(1);
                        mode = sasMode;
                        control.setSASMode(SASMode.fromValue(sasMode));
                    }

                }
                if (sas == 1 && mode != sasMode) {
                    mode = sasMode;
                    System.out.println(mode);
                    try {
                        control.setSASMode(SASMode.fromValue(mode));
                    } catch (Exception e) {
//                        e.printStackTrace();
                    }
                }

                sleep(50);

            }


        } finally {
            if (apoapsis != null)
                apoapsis.remove();
            if (periapsis != null)
                periapsis.remove();
            if (inclination != null)
                inclination.remove();
            if (altitude != null)
                altitude.remove();
            if (vSpeed != null)
                vSpeed.remove();
            if (hSpeed != null)
                hSpeed.remove();
        }
    }

    @SneakyThrows
    private void setupKrpc(Connection connection) {

        krpc = KRPC.newInstance(connection);
        System.out.println(krpc.getCurrentGameScene());

        setupUI(connection);

        spaceCenter = SpaceCenter.newInstance(connection);

    }


    @SneakyThrows
    private Control setupPreFlight(Vessel vessel) {

        System.out.println(vessel.getName());

        Control control = vessel.getControl();
//        control.setSAS(true);
//        control.setSASMode(NORMAL);
//        control.setThrottle(.75f);

        return control;

    }

    private void setupUI(Connection connection) throws RPCException {
        ui = UI.newInstance(connection);
        msg("Connected", 2);
    }

    private void msg(String message, int sec) throws RPCException {
        ui.message(message, sec, TOP_CENTER, new Triplet<>(0d, 255d, 255d), 40);
    }

}
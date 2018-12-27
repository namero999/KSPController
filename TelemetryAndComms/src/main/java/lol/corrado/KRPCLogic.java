package lol.corrado;

import krpc.client.Connection;
import krpc.client.RPCException;
import krpc.client.Stream;
import krpc.client.services.KRPC;
import krpc.client.services.SpaceCenter;
import krpc.client.services.SpaceCenter.Control;
import krpc.client.services.UI;
import lombok.SneakyThrows;
import org.javatuples.Triplet;

import static java.lang.Thread.sleep;
import static java.nio.charset.StandardCharsets.US_ASCII;
import static krpc.client.services.SpaceCenter.SASMode.STABILITY_ASSIST;
import static krpc.client.services.UI.MessagePosition.TOP_CENTER;
import static lol.corrado.serial.KCCSerial.padRight;

public class KRPCLogic {

    private KRPC krpc;
    private UI ui;

    private SpaceCenter spaceCenter;

    @SneakyThrows
    public void start() {

        Stream<Double> altitude = null;
        Stream<Double> apoapsis = null;
        Stream<Double> periapsis = null;
        Stream<Double> inclination = null;

        try (Connection connection = Connection.newInstance()) {

            setupKrpc(connection);

            SpaceCenter.Vessel vessel = spaceCenter.getActiveVessel();
            setupPreFlight(vessel);
            GameData.vesselName = padRight(vessel.getName(), 20).getBytes(US_ASCII);


            SpaceCenter.Flight flight = vessel.flight(vessel.getSurfaceReferenceFrame());

            altitude = connection.addStream(flight, "getMeanAltitude");
            apoapsis = connection.addStream(vessel.getOrbit(), "getApoapsisAltitude");
            periapsis = connection.addStream(vessel.getOrbit(), "getPeriapsisAltitude");
            inclination = connection.addStream(vessel.getOrbit(), "getInclination");

            // Activate the first stage
//            vessel.getControl().activateNextStage();
//            vessel.getAutoPilot().engage();
//            vessel.getAutoPilot().targetPitchAndHeading(90, 90);
//            vessel.getAutoPilot().setTargetRoll(90);

            while (true) {

                GameData.apoapsisMeters = (float) (double) apoapsis.get();
                GameData.periapsisMeters = (float) (double) periapsis.get();
                GameData.inclinationDegrees = (float) Math.toDegrees(inclination.get());

                sleep(20);

            }


        } finally {
            if (altitude != null)
                altitude.remove();
            if (apoapsis != null)
                apoapsis.remove();
            if (periapsis != null)
                periapsis.remove();
            if (inclination != null)
                inclination.remove();
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
    private Control setupPreFlight(SpaceCenter.Vessel vessel) {

        System.out.println(vessel.getName());

        Control control = vessel.getControl();
        control.setSAS(true);
        control.setSASMode(STABILITY_ASSIST);
        control.setThrottle(.75f);

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
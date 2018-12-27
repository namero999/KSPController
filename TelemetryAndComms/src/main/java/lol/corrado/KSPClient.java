package lol.corrado;

import krpc.client.Connection;
import krpc.client.RPCException;
import krpc.client.Stream;
import krpc.client.StreamException;
import krpc.client.services.KRPC;
import krpc.client.services.SpaceCenter;
import krpc.client.services.SpaceCenter.Control;
import krpc.client.services.SpaceCenter.Flight;
import krpc.client.services.SpaceCenter.Vessel;
import krpc.client.services.UI;
import org.javatuples.Triplet;

import java.io.IOException;

import static java.lang.String.format;
import static java.lang.Thread.sleep;
import static krpc.client.services.SpaceCenter.SASMode.STABILITY_ASSIST;
import static krpc.client.services.UI.MessagePosition.TOP_CENTER;

public class KSPClient {

    public static KRPC krpc;
    public static UI ui;
    public static SpaceCenter spaceCenter;

    public static void main(String[] args) throws IOException, RPCException, InterruptedException, StreamException {

        try (Connection connection = Connection.newInstance()) {

            krpc = KRPC.newInstance(connection);
            System.out.println(krpc.getCurrentGameScene());
            setupUI(connection);

            spaceCenter = SpaceCenter.newInstance(connection);
            Vessel vessel = spaceCenter.getActiveVessel();

            Control control = setupPreFlight(vessel);
            Flight flight = vessel.flight(vessel.getSurfaceReferenceFrame());

            Stream<Float> altitude = connection.addStream(flight, "getMeanAltitude");
            Stream<Float> apoapsis = connection.addStream(vessel.getOrbit(), "getApoapsisAltitude");
            Stream<Float> boosterFuel = connection.addStream(vessel.resourcesInDecoupleStage(3, false), "amount", "LiquidFuel");

            float turnStartAltitude = 300;
            float turnEndAltitude = 45000;
            float targetAltitude = 150000;
            double turnAngle = 0;

            boolean boosterSeparated = false;

            // Activate the first stage
            vessel.getControl().activateNextStage();
            vessel.getAutoPilot().engage();
            vessel.getAutoPilot().targetPitchAndHeading(90, 90);
            vessel.getAutoPilot().setTargetRoll(90);

            while (true) {

                // BOOSTER SEPARATION WITH EVENTS

//                ProcedureCall solidFuel = connection.getCall(boosterStage, "amount", "LiquidFuel");
//
//                Event event = krpc.addEvent(lessThan(connection,
//                        Expression.call(connection, solidFuel),
//                        Expression.constantFloat(connection, .1f)));
//
//                synchronized (event.getCondition()) {
//                    event.waitFor();
//                }
//
//                msg("Booster separation", 2);
//                vessel.getControl().activateNextStage();
//                inOrbit = true;

                // Gravity turn
                if (altitude.get() > turnStartAltitude && altitude.get() < turnEndAltitude) {
                    double frac = (altitude.get() - turnStartAltitude) / (turnEndAltitude - turnStartAltitude);
                    double newTurnAngle = frac * 90.0;
                    if (Math.abs(newTurnAngle - turnAngle) > 0.5) {
                        turnAngle = newTurnAngle;
                        vessel.getAutoPilot().targetPitchAndHeading((float) (90 - turnAngle), 90);
                    }
                }

                // Decrease throttle when approaching target apoapsis
                if (apoapsis.get() > targetAltitude * 0.9) {

                    System.out.println(format("Approaching target apoapsis (%s) %s", targetAltitude, apoapsis.get()));

                    control.setThrottle(0.25f);

                    while (apoapsis.get() < targetAltitude)
                        System.out.println(apoapsis.get());

                    System.out.println("Target apoapsis reached");

                    performBoosterSeparation(control);

                    break;
                }

                sleep(1000);

            }

            System.out.println("--out of loop!!");

            while (altitude.get() < 71000) {
                sleep(1000);
            }

            System.out.println("in space");
            control.activateNextStage(); // Fairings

            flight = vessel.flight(vessel.getOrbitalReferenceFrame());
            System.out.println(flight.getPrograde());
            vessel.getAutoPilot().setTargetDirection(flight.getPrograde());


            System.out.println(targetAltitude - 100);
            while (altitude.get() < targetAltitude - 100) {
            }

            System.out.println("done");


            altitude.remove();
            boosterFuel.remove();
            apoapsis.remove();

        }

    }

    private static boolean performBoosterSeparation(Control control) throws RPCException, InterruptedException {

        msg("Booster separation", 1);

        control.setThrottle(0);
        sleep(500);

        control.activateNextStage();
        sleep(1000);

//        control.setThrottle(.2f);
//        sleep(2000);

//        msg("Full Throttle", 2);
//        control.setThrottle(1);

        msg("Booster separation COMPLETED", 1);

        return true;

    }

    private static Control setupPreFlight(Vessel vessel) throws RPCException {

        System.out.println(vessel.getName());

        Control control = vessel.getControl();
        control.setSAS(true);
        control.setSASMode(STABILITY_ASSIST);
        control.setThrottle(.75f);

        return control;

    }

    private static void setupUI(Connection connection) throws RPCException {

        ui = UI.newInstance(connection);

        msg("Connected", 2);

//        UI.Canvas canvas = ui.getStockCanvas();
//
//        // Get the size of the game window in pixels
//        Pair<Double, Double> screenSize = canvas.getRectTransform().getSize();
//
//        // Add a panel to contain the UI elements
//        UI.Panel panel = canvas.addPanel(true);
//
//        // Position the panel on the left of the screen
//        UI.RectTransform rect = panel.getRectTransform();
//        rect.setSize(new Pair<>(200.0, 100.0));
//        rect.setPosition(new Pair<>((110 - (screenSize.getValue0()) / 2), 0.0));
//
//        // Add a button to set the throttle to maximum
//        UI.Button button = panel.addButton("Full Throttle", true);
//        button.getRectTransform().setPosition(new Pair<>(0.0, 20.0));
//
//        // Add some text displaying the total engine thrust
//        UI.Text text = panel.addText("Thrust: 0 kN", true);
//        text.getRectTransform().setPosition(new Pair<>(0.0, -20.0));
//        text.setColor(new Triplet<>(1.0, 1.0, 1.0));
//        text.setSize(18);
    }

    private static void msg(String message, int sec) throws RPCException {
        ui.message(message, sec, TOP_CENTER, new Triplet<>(0d, 255d, 255d), 40);
    }

}

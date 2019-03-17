package lol.corrado;

import com.fazecast.jSerialComm.SerialPort;
import lol.corrado.serial.PullCommandsThread;
import lol.corrado.serial.PushTelemetryThread;

import static lol.corrado.serial.KCCSerial.startSerial;

public class KSPClientAndSerialWrite {

    public static void main(String[] args) {

        SerialPort serial = startSerial();

        PushTelemetryThread push = new PushTelemetryThread(serial);
        new Thread(push).start();
        PullCommandsThread pull = new PullCommandsThread(serial);
        new Thread(pull).start();

        try {
            new KRPCLogic().start();
        } catch (Exception e) {
            push.setShouldStop(true);
            pull.setShouldStop(true);
        }

    }

}
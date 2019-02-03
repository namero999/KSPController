package lol.corrado;

import com.fazecast.jSerialComm.SerialPort;
import lol.corrado.serial.PullCommandsThread;
import lol.corrado.serial.PushTelemetryThread;

import static lol.corrado.serial.KCCSerial.startSerial;

public class KSPClientAndSerialWrite {

    public static void main(String[] args) {

        SerialPort serial = startSerial();

        new Thread(new PushTelemetryThread(serial)).start();
        new Thread(new PullCommandsThread(serial)).start();

//        new KRPCLogic().start();

    }

}
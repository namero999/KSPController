package lol.corrado;

import com.fazecast.jSerialComm.SerialPort;
import lol.corrado.serial.DataPushingThread;

import static lol.corrado.serial.KCCSerial.startSerial;

public class KSPClientAndSerialWrite {

    public static void main(String[] args) {

        SerialPort serial = startSerial();
        new Thread(new DataPushingThread(serial)).start();
//        new KRPCLogic().start();

    }

}
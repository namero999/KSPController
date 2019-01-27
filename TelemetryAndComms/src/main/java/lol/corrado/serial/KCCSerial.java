package lol.corrado.serial;

import com.fazecast.jSerialComm.SerialPort;

import static com.fazecast.jSerialComm.SerialPort.*;
import static lol.corrado.utils.Utils.sleep;

public class KCCSerial {

    private static final int BAUD = 57600;

    public static final byte SYN = 0x5E; // ^
    public static final byte ACK = 0x7E; // ~
    public static final byte END = 0x17;

    private static SerialPort port;

    public static SerialPort startSerial() {

        SerialPort[] ports = SerialPort.getCommPorts();
        port = ports[0];
        port.setComPortParameters(BAUD, 8, ONE_STOP_BIT, NO_PARITY);
        port.setComPortTimeouts(TIMEOUT_WRITE_BLOCKING | TIMEOUT_READ_BLOCKING, 0, 0);

        if (!port.openPort())
            throw new RuntimeException("Failed to open serial port");

        sleep(5_000);

        handshake();

        return port;

    }

    private static void handshake() {

        byte[] buffer = new byte[] { SYN };

        port.writeBytes(buffer, 1);

        while (port.readBytes(buffer, 1) != 1 && buffer[0] != ACK) ;

        System.out.println("Jeb Has Arrived!");

    }

}
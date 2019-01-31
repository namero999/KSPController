package lol.corrado.serial;

import com.fazecast.jSerialComm.SerialPort;

import static com.fazecast.jSerialComm.SerialPort.*;
import static lol.corrado.utils.Utils.sleep;

public class KCCSerial {

    private static final int BAUD = 57600;

    public static final byte SYN = 0x16;
    public static final byte ACK = 0x06;
    public static final byte NAK = 0x15;

    public static final byte DC1 = 0x11;
    public static final byte DC2 = 0x12;
    public static final byte DC3 = 0x13;
    public static final byte DC4 = 0x14;

    public static final byte[] HS_START = { SYN };
    public static final byte[] START = { DC1, DC2 };
    public static final byte[] END = { DC3, DC4 };

    private static SerialPort port;

    public static SerialPort startSerial() {

        SerialPort[] ports = SerialPort.getCommPorts();

        port = ports[0];
        port.setComPortParameters(BAUD, 8, ONE_STOP_BIT, NO_PARITY);
        port.setComPortTimeouts(TIMEOUT_WRITE_BLOCKING | TIMEOUT_READ_BLOCKING, 0, 0);

        if (!port.openPort())
            throw new RuntimeException("Failed to open serial port");

        sleep(2_000);

        handshake();

        return port;

    }

    private static void handshake() {

        byte[] buffer = new byte[1];

        do {
            port.writeBytes(HS_START, HS_START.length);
        } while (port.readBytes(buffer, 1) < 1 && buffer[0] != ACK);

        System.out.println("Jeb Has Arrived!");

    }

}
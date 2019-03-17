package lol.corrado.model;

import java.nio.ByteBuffer;

import static java.nio.ByteOrder.LITTLE_ENDIAN;

public class ControlData {

    public static final byte[] raw = new byte[8];

    private static final ByteBuffer BUFFER;

    static {
        BUFFER = ByteBuffer.wrap(raw);
        BUFFER.order(LITTLE_ENDIAN);
    }

    public static short attX;
    public static short attY;
    public static short attZ;
    public static byte sasOn = 0;
    public static byte sasMode = 0;

    public static void load() {

        BUFFER.position(0);

        attX = BUFFER.getShort();
        attY = BUFFER.getShort();
        attZ = BUFFER.getShort();
        sasOn = BUFFER.get();
        sasMode = BUFFER.get();

    }

}
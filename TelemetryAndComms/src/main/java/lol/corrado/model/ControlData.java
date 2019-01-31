package lol.corrado.model;

import lombok.experimental.UtilityClass;

import java.nio.ByteBuffer;

import static java.nio.ByteOrder.LITTLE_ENDIAN;

@UtilityClass
public class ControlData {

    public final byte[] raw = new byte[6];

    private final ByteBuffer BUFFER;

    static {
        BUFFER = ByteBuffer.wrap(raw);
        BUFFER.order(LITTLE_ENDIAN);
    }

    public short x;
    public short y;
    public short z;

    public void load() {

        BUFFER.position(0);

        x = BUFFER.getShort();
        y = BUFFER.getShort();
        z = BUFFER.getShort();

        System.out.println();

    }

}
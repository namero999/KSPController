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

    public short attX;
    public short attY;
    public short attZ;

    public void load() {

        BUFFER.position(0);

        attX = BUFFER.getShort();
        attY = BUFFER.getShort();
        attZ = BUFFER.getShort();

    }

}
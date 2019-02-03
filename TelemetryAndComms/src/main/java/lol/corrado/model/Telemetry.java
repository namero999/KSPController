package lol.corrado.model;

import lombok.experimental.UtilityClass;

import java.nio.ByteBuffer;

import static java.nio.ByteOrder.LITTLE_ENDIAN;
import static lol.corrado.utils.Utils.toChars;

@UtilityClass
public class Telemetry {

    public final byte[] raw = new byte[48];

    private final ByteBuffer BUFFER;

    static {
        BUFFER = ByteBuffer.wrap(raw);
        BUFFER.order(LITTLE_ENDIAN);
    }

    // ORBITAL
    public byte[] vesselName = toChars("Vessel");

    public float apoapsisMeters = 10;
    public float periapsisMeters = 20;
    public float inclinationDegrees = 30;

    // SURFACE
    public byte[] body = toChars("Kerbin");

    public float altitude = 40;
    public float vSpeed = 50;
    public float hSpeed = 60;

    public short fuelSolid = 10;

    public byte[] getBytes() {

        BUFFER.position(0);

        BUFFER.put(vesselName);
        BUFFER.putFloat(apoapsisMeters += .01);
        BUFFER.putFloat(periapsisMeters++);
        BUFFER.putFloat(inclinationDegrees++);

        BUFFER.put(body);
        BUFFER.putFloat(altitude++);
        BUFFER.putFloat(vSpeed += .01);
        BUFFER.putFloat(hSpeed++);

        BUFFER.putShort(fuelSolid);

        return raw;

    }

}
package lol.corrado.model;

import lombok.experimental.UtilityClass;

import static java.lang.Float.floatToIntBits;
import static java.lang.System.arraycopy;
import static lol.corrado.utils.Utils.intToBytes;
import static lol.corrado.utils.Utils.toChars;

@UtilityClass
public class GameData {

    // ORBITAL
    public byte[] vesselName = toChars("VESSEL");

    public float apoapsisMeters = 10;
    public float periapsisMeters = 20;
    public float inclinationDegrees = 30;

    // SURFACE
    public byte[] body = toChars("BODY");

    public float altitude = 40;
    public float vSpeed = 50;
    public float hSpeed = 60;

    public byte[] getBytes() {

        byte[] res = new byte[

                vesselName.length

                        + 4 + 4 + 4

                        + body.length

                        + 4 + 4 + 4

                ];

        arraycopy(vesselName, 0, res, 0, vesselName.length);

        arraycopy(intToBytes(floatToIntBits(apoapsisMeters += .01)), 0, res, 11, 4);
        arraycopy(intToBytes(floatToIntBits(periapsisMeters++)), 0, res, 15, 4);
        arraycopy(intToBytes(floatToIntBits(inclinationDegrees++)), 0, res, 19, 4);

//        arraycopy(shortToBytes(g), 0, res, 16, 2);

        arraycopy(body, 0, res, 23, body.length);

        arraycopy(intToBytes(floatToIntBits(altitude++)), 0, res, 34, 4);
        arraycopy(intToBytes(floatToIntBits(vSpeed += 0.01)), 0, res, 38, 4);
        arraycopy(intToBytes(floatToIntBits(hSpeed++)), 0, res, 42, 4);

        return res;

    }

}
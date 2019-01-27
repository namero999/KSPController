package lol.corrado.model;

import lombok.experimental.UtilityClass;

import static java.lang.Float.floatToIntBits;
import static java.lang.System.arraycopy;
import static lol.corrado.serial.KCCSerial.END;
import static lol.corrado.utils.Utils.intToBytes;
import static lol.corrado.utils.Utils.toChars;

@UtilityClass
public class GameData {

    public byte[] vesselName = toChars("VESSEL");

    // ORBITAL
    public float apoapsisMeters = 1;
    public float periapsisMeters = 2;
    public float inclinationDegrees = 3;

    public byte[] body = toChars("BODY");

    public float altitude = 4;
    public float vSpeed = 5;
    public float hSpeed = 6;

    public byte[] getBytes() {

        byte[] res = new byte[

                vesselName.length

                        + 4 + 4 + 4

                        + body.length

                        + 4 + 4 + 4

                        + 1
                ];

        arraycopy(vesselName, 0, res, 0, vesselName.length);

        arraycopy(intToBytes(floatToIntBits(apoapsisMeters)), 0, res, 11, 4);
        arraycopy(intToBytes(floatToIntBits(periapsisMeters)), 0, res, 15, 4);
        arraycopy(intToBytes(floatToIntBits(inclinationDegrees)), 0, res, 19, 4);

//        arraycopy(shortToBytes(g), 0, res, 16, 2);

        arraycopy(body, 0, res, 23, body.length);

        arraycopy(intToBytes(floatToIntBits(altitude)), 0, res, 34, 4);
        arraycopy(intToBytes(floatToIntBits(vSpeed)), 0, res, 38, 4);
        arraycopy(intToBytes(floatToIntBits(hSpeed)), 0, res, 42, 4);


        res[res.length - 1] = END;

        return res;

    }

}
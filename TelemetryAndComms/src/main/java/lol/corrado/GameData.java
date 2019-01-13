package lol.corrado;

import lombok.experimental.UtilityClass;

import static java.lang.Float.floatToIntBits;
import static java.lang.System.arraycopy;
import static lol.corrado.utils.Utils.intToBytes;
import static lol.corrado.utils.Utils.shortToBytes;

@UtilityClass
public class GameData {

    public byte[] vesselName;
    public float apoapsisMeters;
    public float periapsisMeters;
    public float inclinationDegrees;
    public short g = 0;

    public byte[] getBytes() {

        byte[] res = new byte[4 + 4 + 4 + 2];
        arraycopy(intToBytes(floatToIntBits(apoapsisMeters)), 0, res, 0, 4);
        arraycopy(intToBytes(floatToIntBits(periapsisMeters)), 0, res, 4, 4);
        arraycopy(intToBytes(floatToIntBits(inclinationDegrees)), 0, res, 8, 4);
        arraycopy(shortToBytes(g), 0, res, 12, 2);
        return res;

    }

}
package lol.corrado.utils;

import lombok.SneakyThrows;

import static java.lang.System.arraycopy;
import static java.nio.charset.StandardCharsets.US_ASCII;

public class Utils {

    public static byte[] shortToBytes(short val) {
        return new byte[] {
                (byte) val,
                (byte) (val >> 8) };
    }

    public static byte[] intToBytes(int val) {
        return new byte[] {
                (byte) val,
                (byte) (val >> 8),
                (byte) (val >> 16),
                (byte) (val >> 24) };
    }

    public static byte[] longToBytes(long val) {
        return new byte[] {
                (byte) (val >> 56),
                (byte) (val >> 48),
                (byte) (val >> 40),
                (byte) (val >> 32),
                (byte) (val >> 24),
                (byte) (val >> 16),
                (byte) (val >> 8),
                (byte) val };
    }

    @SneakyThrows
    public static void sleep(long millis) {
        Thread.sleep(millis);
    }

    public static byte[] toChars(String s) {
        byte[] nulls = new byte[] { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
        if (s == null || s.isEmpty()) return nulls;
        byte[] bytes = s.getBytes(US_ASCII);
        arraycopy(bytes, 0, nulls, 0, bytes.length);
        return nulls;
    }

}
package lol.corrado.utils;

import lombok.SneakyThrows;

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

}
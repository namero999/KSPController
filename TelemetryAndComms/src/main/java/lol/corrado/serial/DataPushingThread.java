package lol.corrado.serial;

import com.fazecast.jSerialComm.SerialPort;
import lol.corrado.model.GameData;
import lombok.NonNull;
import lombok.RequiredArgsConstructor;
import lombok.Setter;
import lombok.SneakyThrows;

import static lol.corrado.serial.KCCSerial.*;

@RequiredArgsConstructor
public class DataPushingThread implements Runnable {

    @NonNull
    private SerialPort serial;

    @Setter
    private boolean shouldStop = false;

    @Override
    @SneakyThrows
    public void run() {

        do {
            byte[] bytes = GameData.getBytes();
            serial.writeBytes(START, START.length);
            serial.writeBytes(bytes, bytes.length);
            serial.writeBytes(END, END.length);
            byte b = (byte) serial.getInputStream().read();
            if (b == NAK)
                System.out.println("NAK!");
        } while (!shouldStop);

    }

}
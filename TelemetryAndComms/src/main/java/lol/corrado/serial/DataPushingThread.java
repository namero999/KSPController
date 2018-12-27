package lol.corrado.serial;

import com.fazecast.jSerialComm.SerialPort;
import lol.corrado.GameData;
import lombok.NonNull;
import lombok.RequiredArgsConstructor;
import lombok.Setter;
import lombok.SneakyThrows;

import static lol.corrado.serial.KCCSerial.SYN;

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
            serial.writeBytes(bytes, bytes.length);
        } while (!shouldStop && serial.getInputStream().read() == SYN);

    }

}
package lol.corrado.serial;

import com.fazecast.jSerialComm.SerialPort;
import lol.corrado.model.ControlData;
import lombok.NonNull;
import lombok.RequiredArgsConstructor;
import lombok.SneakyThrows;

@RequiredArgsConstructor
public class PullCommandsThread implements Runnable {

    @NonNull
    private SerialPort serial;

    @Override
    @SneakyThrows
    public void run() {

        byte[] buf = new byte[10];

        do {
            serial.readBytes(buf, buf.length);
            System.arraycopy(buf, 2, ControlData.raw, 0, ControlData.raw.length);
            ControlData.load();
            System.out.print(ControlData.x+"\r");
        } while (true);

    }

}
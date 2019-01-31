package lol.corrado.serial;

import com.fazecast.jSerialComm.SerialPort;
import lol.corrado.model.Telemetry;
import lombok.NonNull;
import lombok.RequiredArgsConstructor;
import lombok.Setter;
import lombok.SneakyThrows;

import static lol.corrado.serial.KCCSerial.END;
import static lol.corrado.serial.KCCSerial.START;

@RequiredArgsConstructor
public class PushTelemetryThread implements Runnable {

    @NonNull
    private SerialPort serial;

    @Setter
    private boolean shouldStop = false;

    @Override
    @SneakyThrows
    public void run() {

        do {
            byte[] bytes = Telemetry.getBytes();
            serial.writeBytes(START, START.length);
            serial.writeBytes(bytes, bytes.length);
            serial.writeBytes(END, END.length);
        } while (!shouldStop);

    }

}
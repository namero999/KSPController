package lol.corrado.serial;

import com.fazecast.jSerialComm.SerialPort;
import lol.corrado.model.ControlData;
import lombok.NonNull;
import lombok.RequiredArgsConstructor;
import lombok.Setter;
import lombok.SneakyThrows;

import java.io.InputStream;

import static lol.corrado.serial.KCCSerial.*;


@RequiredArgsConstructor
public class PullCommandsThread implements Runnable {

    @NonNull
    private SerialPort serial;

    @Setter
    private boolean shouldStop = false;

    @Override
    public void run() {
        allBytes();
//        oneByte();
    }

    @SneakyThrows
    public void allBytes() {

        InputStream input = serial.getInputStream();

        boolean progress = false;

        do {

            if (progress) {

                progress = false;

                serial.readBytes(ControlData.raw, ControlData.raw.length);

                if (input.read() == DC3 && input.read() == DC4) {

                    ControlData.load();

                }

            } else if (input.read() == DC1 && input.read() == DC2)
                progress = true;

        } while (!shouldStop);

    }

    @SneakyThrows
    public void oneByte() {

        InputStream input = serial.getInputStream();

        boolean progress = false;
        int index = 0;

        do {

            if (progress) {

                if (index < ControlData.raw.length) {
                    serial.readBytes(ControlData.raw, 1, index++);
                } else {

                    progress = false;
                    index = 0;

                    if (input.read() == DC3 && input.read() == DC4) {

                        ControlData.load();

                    }

                }

            } else if (input.read() == DC1 && input.read() == DC2)
                progress = true;

        } while (!shouldStop);

    }

}
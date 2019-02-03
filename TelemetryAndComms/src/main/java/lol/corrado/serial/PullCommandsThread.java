package lol.corrado.serial;

import com.fazecast.jSerialComm.SerialPort;
import lol.corrado.model.ControlData;
import lol.corrado.model.Telemetry;
import lombok.NonNull;
import lombok.RequiredArgsConstructor;
import lombok.SneakyThrows;

import java.io.InputStream;

import static lol.corrado.model.ControlData.attX;
import static lol.corrado.serial.KCCSerial.*;

@RequiredArgsConstructor
public class PullCommandsThread implements Runnable {

    @NonNull
    private SerialPort serial;

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
                    Telemetry.fuelSolid = (short) Math.abs((attX / 10));

                }

            } else if (input.read() == DC1 && input.read() == DC2)
                progress = true;

        } while (true);

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
                        Telemetry.fuelSolid = (short) Math.abs((attX / 10));

                    }

                }

            } else if (input.read() == DC1 && input.read() == DC2)
                progress = true;

        } while (true);

    }

}
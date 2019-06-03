package com.company;

import java.lang.ref.Reference;
import java.util.Arrays;
import java.util.concurrent.CyclicBarrier;

public class CyclicBarrierTest {

    public static void main(String[] args) {

        int N = 6;
        float[][] m = {
            {Float.parseFloat(args[0]), Float.parseFloat(args[1]), Float.parseFloat(args[2])},
            {Float.parseFloat(args[3]), Float.parseFloat(args[4]), Float.parseFloat(args[5])},
            {Float.parseFloat(args[6]), Float.parseFloat(args[7]), Float.parseFloat(args[8])}
        };
        float[] buffer = {0, 0, 0, 0, 0, 0};

        CyclicBarrier barrier = new CyclicBarrier(N, new Runnable() {
            private int count = 1;

            @Override
            public void run() {
                System.out.println("Barreira superada..!! " + (count++) + "x");
                float determinant = buffer[0] + buffer[1] + buffer[2] - buffer[3] - buffer[4] - buffer[5];
                System.out.println(Arrays.toString(buffer));
                System.out.println("Determinant: " + determinant);
            }
        });

        float[][] factors = {
                {m[0][0], m[1][1], m[2][2]},
                {m[0][1], m[1][2], m[2][0]},
                {m[0][2], m[1][0], m[2][1]},
                {m[0][2], m[1][1], m[2][0]},
                {m[0][0], m[1][2], m[2][1]},
                {m[0][1], m[1][0], m[2][2]}
        };

        for (int i = 0; i < N; i++) {
            Thread t = new Thread(new CyclicBarThread(barrier, factors[i], buffer, i));
            t.start();
        }
    }
}

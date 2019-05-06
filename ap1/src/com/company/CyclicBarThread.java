package com.company;

import java.util.concurrent.BrokenBarrierException;
import java.util.concurrent.CyclicBarrier;

public class CyclicBarThread implements Runnable {

    private CyclicBarrier barrier;
    private float[] numbers;
    private float[] resultsBuffer;
    private int resultIndex;

    CyclicBarThread(CyclicBarrier barrier, float[] numbers, float[] resultsBuffer, int resultIndex) {
        this.barrier = barrier;
        this.numbers = numbers;
        this.resultsBuffer = resultsBuffer;
        this.resultIndex = resultIndex;
    }

    @Override
    public void run() {
        try {
            multiplyThreeNumbers();
            System.out.println(Thread.currentThread().getName() + " :: Barreira 1: Esperando o primeiro estágio ser completado");
            awaitBarrier();

            System.out.println(Thread.currentThread().getName() + " :: Thread encerrada");
        } catch (Exception ex) {
            ex.printStackTrace();
        }
    }

    private void multiplyThreeNumbers() {
        resultsBuffer[resultIndex] = numbers[0] * numbers[1] * numbers[2];
    }

    private void awaitBarrier() {
        try {
            barrier.await();
        } catch (InterruptedException e) {
            System.out.println("Interrompida!");
            e.printStackTrace();
        } catch (BrokenBarrierException e) {
            System.out.println("Barreira quebrada");
            e.printStackTrace();
        }
    }
}

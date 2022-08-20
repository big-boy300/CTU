package cz.cvut.k36.omo.hw.hw02;

import java.util.ArrayList;

public class OMOSetEven implements OMOSetView {
    OMOSetView setA;

    public OMOSetEven(OMOSetView setA) {
        this.setA = setA;
    }

    @Override
    public boolean contains(int element) {
        return (setA.contains(element) && (element % 2 == 0));
    }

    @Override
    public int[] toArray() {
        int[] arrA = setA.toArray();
        ArrayList<Integer> evenNumbers = new ArrayList<>();
        int counterOfElements = 0;
        for (int i = 0; i < arrA.length; ++i) {
            if (arrA[i] % 2 == 0) {
                evenNumbers.add(arrA[i]);
                counterOfElements++;
            }
        }
        int[] evenNumbersArr = new int[counterOfElements];
        for (int i = 0; i < counterOfElements; i++) {
            evenNumbersArr[i] = evenNumbers.get(i);
        }
        return evenNumbersArr;
    }

    @Override
    public OMOSetView copy() {
        OMOSet evenNumbersCopy = new OMOSet();
        for (Integer i : this.toArray()) {
            evenNumbersCopy.add(i);
        }
        return evenNumbersCopy;
    }
}
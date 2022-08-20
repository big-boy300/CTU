package cz.cvut.k36.omo.hw.hw02;

import java.util.ArrayList;

public class OMOSetComplement implements OMOSetView {
    OMOSetView setA;
    OMOSetView setB;

    public OMOSetComplement(OMOSetView setA, OMOSetView setB) {
        this.setA = setA;
        this.setB = setB;
    }

    @Override
    public boolean contains(int element) {
        return (setA.contains(element) && !setB.contains(element));
    }

    @Override
    public int[] toArray() {
        ArrayList<Integer> complementOfSetB = new ArrayList<>();
        int counterOfElements = 0;
        for (Integer i : setA.toArray()) {
            if (this.contains(i)) {
                complementOfSetB.add(i);
                counterOfElements++;
            }
        }
        int[] complementOfSetBArr = new int[counterOfElements];
        for (int i = 0; i < counterOfElements; ++i) {
            complementOfSetBArr[i] = complementOfSetB.get(i);
        }
        return complementOfSetBArr;
    }

    @Override
    public OMOSetView copy() {
        OMOSet complementCopy = new OMOSet();
        for (Integer i : this.toArray()) {
            complementCopy.add(i);
        }
        return complementCopy;
    }
}
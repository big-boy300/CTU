package cz.cvut.k36.omo.hw.hw02;

import java.util.ArrayList;

public class OMOSetIntersection implements OMOSetView {
    OMOSetView setA;
    OMOSetView setB;

    public OMOSetIntersection(OMOSetView setA, OMOSetView setB) {
        this.setA = setA;
        this.setB = setB;
    }

    @Override
    public boolean contains(int element) {
        return (setA.contains(element) && setB.contains(element));
    }

    @Override
    public int[] toArray() {
        int[] arrA = setA.toArray();
        int[] arrB = setB.toArray();
        ArrayList<Integer> intersectionOfSets = new ArrayList<>();
        int counterOfSameElements = 0;
        for (int i = 0; i < arrA.length; ++i) {
            for (int j = 0; j < arrB.length; ++j) {
                if (arrA[i] == arrB[j]) {
                    intersectionOfSets.add(arrA[i]);
                    counterOfSameElements++;
                    break;
                }
            }
        }
        int[] intersectionOfSetsArr = new int[counterOfSameElements];
        for (int i = 0; i < counterOfSameElements; ++i) {
            intersectionOfSetsArr[i] = intersectionOfSets.get(i);
        }
        return intersectionOfSetsArr;
    }

    @Override
    public OMOSetView copy() {
        OMOSet intersectionOfSetsCopy = new OMOSet();
        for (Integer i : this.toArray()) {
            intersectionOfSetsCopy.add(i);
        }
        return intersectionOfSetsCopy;
    }
}

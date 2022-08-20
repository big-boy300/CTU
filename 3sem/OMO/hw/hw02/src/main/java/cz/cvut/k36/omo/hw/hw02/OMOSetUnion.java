package cz.cvut.k36.omo.hw.hw02;

import java.util.HashSet;
import java.util.Set;

public class OMOSetUnion implements OMOSetView {
    OMOSetView setA;
    OMOSetView setB;

    OMOSetUnion(OMOSetView setA, OMOSetView setB) {
        this.setA = setA;
        this.setB = setB;
    }

    @Override
    public boolean contains(int element) {
        return (setA.contains(element) || setB.contains(element));
    }

    @Override
    public int[] toArray() {
        Set<Integer> setC = new HashSet<>();
        for (Integer i : setA.toArray()) {
            setC.add(i);
        }
        for (Integer i : setB.toArray()) {
            setC.add(i);
        }
        int[] combinedSets = new int[setC.size()];
        int idx = 0;
        for (Integer i : setC) {
            combinedSets[idx] = i;
            idx++;
        }
        return combinedSets;
    }

    @Override
    public OMOSetView copy() {
        OMOSet unionOfSetsCopy = new OMOSet();
        for (Integer i : this.toArray()) {
            unionOfSetsCopy.add(i);
        }
        return unionOfSetsCopy;
    }
}

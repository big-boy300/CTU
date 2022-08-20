package cz.cvut.k36.omo.hw.hw02;

import java.util.HashSet;
import java.util.Set;

public class OMOSet extends OMOSetBase implements OMOSetView {
    Set<Integer> set = new HashSet<>();

    @Override
    public void add(int element) {
        set.add(element);
    }

    @Override
    public void remove(int element) {
        set.remove(element);
    }

    @Override
    public boolean contains(int element) {
        return set.contains(element);
    }

    @Override
    public int[] toArray() {
        int size = set.size();
        int[] arrayFromSet = new int[size];
        int idx = 0;
        for (Integer i : set) {
            arrayFromSet[idx] = i;
            idx++;
        }
        return arrayFromSet;
    }

    @Override
    public OMOSetView copy() {
        OMOSet setCopy = new OMOSet();
        for (Integer i : set) {
            setCopy.add(i);
        }
        return setCopy;
    }
}
package cz.cvut.k36.omo.hw.hw02;

public interface OMOSetView {

    boolean contains(int element);

    int[] toArray();

    OMOSetView copy();
}

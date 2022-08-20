package cz.cvut.k36.omo.hw.hw03;

import java.util.ArrayList;
import java.util.NoSuchElementException;

public class InorderIterator implements CustomIterator {
    private Node nextNode;
    private ArrayList<Node> inorderNodes = new ArrayList<>();


    public InorderIterator(Node node) {
        this.nextNode = node;
        inorderTraversal(node);
    }

    private void inorderTraversal(Node node) {
        if (node == null) return;
        inorderTraversal(node.getLeftChild());
        inorderNodes.add(node);
        inorderTraversal(node.getRightChild());
    }

    @Override
    public boolean hasNext() {
        return !inorderNodes.isEmpty();
    }

    @Override
    public int next() {
        if (!hasNext()) {
            throw new NoSuchElementException();
        }
        int nodeRetValue = inorderNodes.remove(0).getContents();
        return nodeRetValue;
    }
}

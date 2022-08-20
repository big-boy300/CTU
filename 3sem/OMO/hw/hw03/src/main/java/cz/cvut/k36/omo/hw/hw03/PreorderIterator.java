package cz.cvut.k36.omo.hw.hw03;

import java.util.ArrayList;
import java.util.NoSuchElementException;

public class PreorderIterator implements CustomIterator {
    private Node nextNode;
    private ArrayList<Node> preorderNodes = new ArrayList<>();

    public PreorderIterator(Node node) {
        this.nextNode = node;
        preorderTraversal(node);
    }

    private void preorderTraversal(Node node) {
        if (node == null) return;
        preorderNodes.add(node);
        preorderTraversal(node.getLeftChild());
        preorderTraversal(node.getRightChild());
    }

    @Override
    public boolean hasNext() {
        return !preorderNodes.isEmpty();
    }

    @Override
    public int next() {
        if (!hasNext()) {
            throw new NoSuchElementException();
        }
        int nodeRetValue = preorderNodes.remove(0).getContents();
        return nodeRetValue;
    }
}

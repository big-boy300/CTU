package cz.cvut.k36.omo.hw.hw03;

import java.util.ArrayList;
import java.util.NoSuchElementException;

public class PostorderIterator implements CustomIterator {
    private Node nextNode;
    private ArrayList<Node> postorderNodes = new ArrayList<>();

    public PostorderIterator(Node node) {
        this.nextNode = node;
        postorderTraversal(node);
    }

    private void postorderTraversal(Node node) {
        if (node == null) return;
        postorderTraversal(node.getLeftChild());
        postorderTraversal(node.getRightChild());
        postorderNodes.add(node);
    }

    @Override
    public boolean hasNext() {
        return !postorderNodes.isEmpty();
    }

    @Override
    public int next() {
        if (!hasNext()) {
            throw new NoSuchElementException();
        }
        int nodeRetValue = postorderNodes.remove(0).getContents();
        return nodeRetValue;
    }
}
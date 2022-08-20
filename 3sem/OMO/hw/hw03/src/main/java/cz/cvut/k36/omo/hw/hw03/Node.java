package cz.cvut.k36.omo.hw.hw03;

public class Node {
    private final int contents;
    private final Node left, right;
    private Node parent;

    public Node(int contents, Node left, Node right) {
        this.contents = contents;
        this.left = left;
        if (left != null) left.parent = this;
        this.right = right;
        if (right != null) right.parent = this;
    }

    public CustomIterator inorderIterator() {
        return new InorderIterator(this);
    }

    public CustomIterator preorderIterator() {
        return new PreorderIterator(this);
    }

    public CustomIterator postorderIterator() {
        return new PostorderIterator(this);
    }

    public Node getLeftChild() {
        return left;
    }

    public Node getRightChild() {
        return right;
    }

    public int getContents() {
        return contents;
    }

}

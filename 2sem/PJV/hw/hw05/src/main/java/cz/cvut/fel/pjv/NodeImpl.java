package cz.cvut.fel.pjv;

public class NodeImpl implements Node {
    private Node left;
    private Node right;
    private int node_value;

    NodeImpl(int value) {
        node_value = value;       
    }
    
    @Override
    public Node getLeft() {
        return left;
    }    

    public void setLeft(Node left_node) {
        this.left = left_node;
    }

    @Override
    public Node getRight() {
        return right;
    }
    
    public void setRight(Node right_node) {
        this.right = right_node;
    }

    @Override
    public int getValue() {
        return node_value;
    }    
    
    public void setValue(int value) {
        this.node_value = value;
    }   
}

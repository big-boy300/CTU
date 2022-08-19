package cz.cvut.fel.pjv;

public class TreeImpl implements Tree {
    private NodeImpl root;
    
    @Override
    public void setTree(int[] values) { 
        if(values.length == 0)
            return;
        
        root = buildTree(values, 0, values.length);
    }
    
    public NodeImpl buildTree(int[] values, int left_side, int right_side){
        if(left_side >= right_side)
            return null;
        
        int new_root = (left_side + right_side)/2;
        NodeImpl new_node = new NodeImpl(values[new_root]);
        
        new_node.setLeft(buildTree(values, left_side, new_root));
        new_node.setRight(buildTree(values, new_root+1, right_side));
        
        return new_node;
    }  
    
    @Override
    public Node getRoot() {
        return root;
    }
    
    @Override
    public String toString(){
        return printTree(root,0);
    }
    
    private String printTree(Node node, int depth){
        if(node == null)
            return "";
               
        String spaces = "";
        String node_str = "- " + node.getValue();       
        String final_str = "";
        
        for(int i = 0; i < depth; ++i)
            spaces += " ";
        
        final_str += spaces + node_str + "\n";
        
        if(node.getLeft() != null)
            final_str += printTree(node.getLeft(), depth+1);        
        
        if(node.getRight() != null)
            final_str += printTree(node.getRight(), depth+1);
            
        return final_str;        
    }
}

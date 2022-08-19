package cz.cvut.fel.pjv;

public class Start {
    public static void main(String[] args) {
        new Start().tree();
    }
    
    private void tree(){
        TreeImpl tree = new TreeImpl();
        int[] array = {1,2,3,4,5,6,7,8,9,10};
        tree.setTree(array);
        System.out.println(tree.toString());       
    }
}

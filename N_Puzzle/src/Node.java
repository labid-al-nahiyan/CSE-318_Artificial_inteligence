import java.lang.reflect.Array;
import java.util.*;

public class Node {
    int f;
    int g;
    int h;
    int hashValue;

    Node parent = null;
    int[][] values ;

    Node(int n){
        values = new int[n][n];
    }
    public int getF() {
        return f;
    }
    public void setF(int f){
        this.f = f;
    }

    public int getG() {
        return g;
    }
    public int getH() {
        return h;
    }
    public void setH(int h) {
        this.h = h;
    }
    public void setG(int g){
        this.g = g;
    }

    public Node getParent() {
        return parent;
    }
    public void setParent(Node parent){
        this.parent = parent;
    }

//    void addRow(int[] row){
//        values.add(row);
//    }

    @Override
    public int hashCode() {

        return Arrays.deepHashCode(values);
    }

    @Override
    public boolean equals(Object o)
    {
        if(this == o)return  true;
        if(o==null || getClass()!=o.getClass())return false;
        return Arrays.deepEquals(values, ((Node)o).values);
    }

    int Hamming(){
        int count = 0;
        for(int i=0;i<values.length;i++){
            for(int j = 0; j< values.length; j++) {
                if (values[i][j] != (i * values.length + j+1) && values[i][j]!=0) {
                    count++;
                }
            }
        }
        return count;
    }
    int Manhattan(){
        int count = 0;
        for(int i=0;i<values.length;i++){
            for(int j = 0; j< values.length; j++) {
                if (values[i][j] != (i * values.length + j+1) && values[i][j]!=0) {
                    int value = values[i][j];
                    int row = (value-1)/values.length;
                    int col = (value-1)% values.length;

                    count += Math.abs(row-i)+Math.abs(col-j);
                }
            }
        }
        return count;
    }
    void takeInput(int n){
        Scanner sc = new Scanner(System.in);

        for(int i=0;i<n;i++){

            for(int j=0;j<n;j++){


                values[i][j] = sc.nextInt();
            }
        }
    }
    void copyValue(){

        for(int i=0;i<this.getParent().values.length;i++){
            for(int j=0; j< this.getParent().values.length; j++)
            {
                this.values[i][j] = this.getParent().values[i][j];
            }
        }
    }
    ArrayList<Node> generateSuccessor(int byManhatton){
        ArrayList<Node> nodes = new ArrayList<>();

        int blank_row = -1, blank_col = -1;

        for(int i=0;i<values.length;i++){
            for(int j=0;j<values.length;j++){
                if(values[i][j] == 0){
                    blank_row = i;
                    blank_col = j;
                    break;
                }
            }
            if(blank_col!=-1)break;
        }

        if(blank_col >= 0 && blank_col != values.length-1){
            int n = values.length;
            Node temp = new Node(n);
            temp.values = new int[n][n];
            temp.setParent(this);
            temp.setG(this.getG()+1);
            temp.setH(this.getH());
            temp.copyValue();
            temp.swapPosition(blank_row,blank_col,blank_row,blank_col+1,byManhatton);
            temp.setF(temp.getG()+ temp.getH());
            nodes.add(temp);
        }
        if(blank_col < values.length && blank_col!=0){
            int n = values.length;
            Node temp = new Node(n);
            temp.values = new int[n][n];
            temp.setParent(this);
            temp.setG(this.getG()+1);
            temp.setH(this.getH());
            temp.copyValue();
            temp.swapPosition(blank_row,blank_col,blank_row,blank_col-1,byManhatton);
            temp.setF(temp.getG()+ temp.getH());
            nodes.add(temp);
        }
        if(blank_row >= 0 && blank_row != values.length-1){
            int n = values.length;
            Node temp = new Node(n);
            temp.values = new int[n][n];
            temp.setParent(this);
            temp.setG(this.getG()+1);
            temp.setH(this.getH());
            temp.copyValue();
            temp.swapPosition(blank_row,blank_col,blank_row+1,blank_col,byManhatton);
            temp.setF(temp.getG()+ temp.getH());
            nodes.add(temp);
        }
        if(blank_row< values.length && blank_row != 0){
            int n = values.length;
            Node temp = new Node(n);
            temp.values = new int[n][n];
            temp.setParent(this);
            temp.setG(this.getG()+1);
            temp.setH(this.getH());
            temp.copyValue();
            temp.swapPosition(blank_row,blank_col,blank_row-1,blank_col,byManhatton);
            temp.setF(temp.getG()+ temp.getH());
            nodes.add(temp);
        }

        return nodes;
    }
    void print(){
        for(int i=0;i<values.length;i++){
            for(int j = 0; j< values.length; j++){
                System.out.print(values[i][j]+" ");
            }
            System.out.println();
        }
        System.out.println();

    }
    void swapPosition(int preRow, int preCol, int currRow, int currCol,int byManhatton){

        this.values[preRow][preCol] = this.values[currRow][currCol];
        this.values[currRow][currCol] = 0;

        int h = this.getH();
        if(byManhatton==1){
            int value = values[preRow][preCol];

            int row = (value-1)/values.length;
            int col = (value-1)% values.length;

            h -= Math.abs(row-currRow)+Math.abs(col-currCol);

            row = (value-1)/values.length;
            col = (value-1)% values.length;
            h += Math.abs(row-preRow)+Math.abs(col-preCol);
//            h = this.Manhattan();
        }
        else{
            if(this.values[preRow][preCol] == currRow*values.length+currCol+1){
                h++;
            }
            else if(this.values[preRow][preCol] == preRow*values.length+preCol+1){
                h--;
            }
        }
        this.setH(h);
    }

    int inversionCount(){
        int count = 0,x = 0;
        int[] arr = new int[values.length * values.length-1];
        for(int i=0;i<values.length;i++){
            for(int j = 0; j< values.length; j++){
                if(values[i][j]!=0){
                    arr[x] = values[i][j];
                    x++;
                }
            }
        }

        for(int i=0;i<arr.length;i++){
            for(int j = i+1;j< arr.length;j++){
                if(arr[i]>arr[j])count++;
            }
        }
        return count;
    }
    Boolean solveAble(){
        int n = values.length;
        int x = this.inversionCount();

        if(n%2==1){
            if(x%2==1){
                return false;
            }
            else{
                return true;
            }
        }
        else{
            int blank_row = -1;

            for(int i=0;i<values.length;i++){
                for(int j=0;j<values.length;j++){
                    if(values[i][j] == 0){
                        blank_row = i;
                        break;
                    }
                }
            }
            if((x+values.length-1-blank_row)%2==1){
                return false;
            }
            else{
                return true;
            }
        }
    }

    Boolean equalMatrix(Node b){
        if(b==null)return  false;

        int n = this.values.length;
        boolean value = true;
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                if(b.values[i][j]!=this.values[i][j]){
                    value = false;
                    break;
                }
            }
            if(!value)break;
        }
        return  value;
    }
}

class NodeComparator implements Comparator<Node> {
    public int compare(Node node1, Node node2) {
        if (node1.getF() > node2.getF())
            return 1;
        else if (node1.getF() < node2.getF())
            return -1;
        else{
            if (node1.g > node2.g)
                return 1;
            else if (node1.g < node2.g)
                return -1;
            else
            return 0;
        }
    }
}

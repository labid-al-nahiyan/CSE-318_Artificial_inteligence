import java.util.*;

public class Main {
    public static void main(String[] args) {

        HashSet<Node> hashtable = new HashSet<>();

        int n;
        Scanner sc=new Scanner(System.in);
        n=sc.nextInt();


        Node start = new Node(n);
        start.takeInput(n);

        if(start.solveAble()==false){
            System.out.println("Unsolvable puzzle");
        }
        else {
            PriorityQueue<Node> pq = new PriorityQueue<>(new NodeComparator());

            int explore=0,expand=0;
            Node leaf = new Node(n);

            start.setH(start.Manhattan());
            start.setG(0);
            start.setF(start.getH());

            pq.add(start);

            while (!pq.isEmpty()) {

                Node u = pq.poll();
                explore++;
                hashtable.add(u);

                if (u.getH() == 0) {
                    leaf = u;

                    break;
                }
                ArrayList<Node> suscessor = (ArrayList<Node>) u.generateSuccessor(1);
                for (int i = 0; i < suscessor.size(); i++) {
                    if (!(hashtable.contains(suscessor.get(i)))) {
                        pq.add(suscessor.get(i));
                        expand++;
                    }
//                    if(suscessor.get(i).equalMatrix(suscessor.get(i).getParent().getParent())==false){
//                        pq.add(suscessor.get(i));
//                    }

                }
            }

            ArrayList<Node> answers = new ArrayList<>();
            while (leaf.getParent() != null) {
                answers.add(leaf);
                leaf = leaf.getParent();
            }

            System.out.println("Minimum number of moves = " + answers.size());

            answers.add(leaf);
            for (int i = answers.size() - 1; i >= 0; i--) {
                answers.get(i).print();
            }
            System.out.println("Explore : "+explore +", Expand : "+expand);

        }
    }
}
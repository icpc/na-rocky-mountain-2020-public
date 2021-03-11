import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.Scanner;

public class interviewqueue_da {

    private void work() {
        Scanner sc = new Scanner(new BufferedReader(new InputStreamReader(System.in)));
        int n = sc.nextInt();
        int[][] a = new int[2][n];
        for (int i = 0; i < n; i++) a[0][i] = sc.nextInt();

        int cur = 0;
        int[] nn = new int[2];
        nn[cur] = n;
        int r = 0;
        StringBuilder sb = new StringBuilder("\n");

        while (true) {
            nn[1 - cur] = 0;
            boolean print = false;

            if (nn[cur] == 1 || a[cur][0] >= a[cur][1]) {
                a[1 - cur][nn[1 - cur]++] = a[cur][0];
            } else {
                sb.append(a[cur][0]);
                sb.append(' ');
                print = true;
            }

            for (int i = 1; i < nn[cur] - 1; i++) {
                if (a[cur][i] >= a[cur][i - 1] && a[cur][i] >= a[cur][i + 1]) {
                    a[1 - cur][nn[1 - cur]++] = a[cur][i];
                } else {
                    sb.append(a[cur][i]);
                    sb.append(' ');
                    print = true;
                }
            }

            if (nn[cur] > 1) {
                if (a[cur][nn[cur] - 1] >= a[cur][nn[cur] - 2]) {
                    a[1 - cur][nn[1 - cur]++] = a[cur][nn[cur] - 1];
                } else {
                    sb.append(a[cur][nn[cur] - 1]);
                    sb.append(' ');
                    print = true;
                }
            }

            cur = 1 - cur;
            if(print) sb.append('\n'); else break;
            r++;
        }

        for (int i = 0; i < nn[cur]; i++) {
            sb.append(a[cur][i]);
            sb.append(' ');
        }

        sb.insert(0, r);
        System.out.print(sb);
        System.out.flush();
    }

    public static void main(String[] args) {
        new interviewqueue_da().work();
    }
}

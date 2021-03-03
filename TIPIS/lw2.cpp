import java.util.ArrayList;
import java.util.HashMap;
import java.util.*;

public class GlobalMembers {

        public static ArrayList<ArrayList<Double>> p = new ArrayList<ArrayList<Double>>();
        public static HashMap<Character, ArrayList<Integer>> bin_representation_for_letter = new HashMap<Character, ArrayList<Integer>>();
    public static String ToBitString(char letter)
    {
        String res = "";
        for (int bit : bin_representation_for_letter.get(letter))
        {
            res += String.valueOf(bit);
        }
        return res;

    }
    public static double ConditionalProbability(char received_letter, char sent_letter)
    {
        double res = 1;
        for (int i = 0; i < 4; ++i)
        {
            res *= p.get((bin_representation_for_letter.get(received_letter))[i]).get((bin_representation_for_letter.get(sent_letter))[i]);
        }
        return res;
    }
    public static <ofstream> void main(String[] args)
    {
        char letter = 'a';
        boolean flag = false;
        for (int b3 = 0; b3 < 2; ++b3)
        {
            for (int b2 = 0; b2 < 2; ++b2)
            {
                for (int b1 = 0; b1 < 2; ++b1)
                {
                    for (int b0 = 0; b0 < 2; ++b0)
                    {
// skip "0000" for lab #3
                        if (!flag)
                        {
                            flag = true;
                            continue;
                        }
                        if (letter > 'k')
                        {
                            break;
                        }
                        bin_representation_for_letter.put(letter, {b3, b2, b1, b0});
                        ++letter;
                    }
                }
            }
        }
        String source_alphabet = new String('a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k');
        String receiver_alphabet = source_alphabet + '?';
// conditional probability
        
        p = tangible.VectorHelper.<Double>nestedArrayList(2, 2);
        p.get(0).set(0, 0.58);
        p.get(1).set(0, 0.42);
        p.get(1).set(1, 0.67);
        p.get(0).set(1, 0.33);
        HashMap<Character, HashMap<Character, Double>> channel_matrix = new HashMap<Character, HashMap<Character, Double>>();
        for (char sent_letter : source_alphabet)
        {
            double sum = 0;
            for (char received_letter : receiver_alphabet)
            {
                if (received_letter == '?')
                {
                    continue;
                }
                channel_matrix.get(sent_letter).put(received_letter, ConditionalProbability(received_letter, sent_letter));
                sum += channel_matrix.get(sent_letter).get(received_letter);
            }
// probability of '????'
            channel_matrix.get(sent_letter).put('?', 1 - sum);
        }
        ofstream fout = new ofstream("C:\\Users\\gosha\\Desktop\\information-theory-lab-2-channel-matrix.txt");
        fout << setprecision(8) << fixed;
        int size_of_cell = 15;
        fout << "CHANNEL MATRIX:" << "\n";
        fout << setw(2 * size_of_cell) << "";
        for (char received_letter : receiver_alphabet)
        {
            fout << setw(size_of_cell) << received_letter;
        }
        fout << "\n";
        fout << setw(2 * size_of_cell) << "";
        for (char received_letter : receiver_alphabet)
        {
            if (received_letter == '?')
            {
                continue;
            }
            fout << setw(size_of_cell) << ToBitString(received_letter);
        }
        fout << setw(size_of_cell) << "????" << "\n";
        for (char sent_letter : source_alphabet)
        {
            fout << setw(size_of_cell) << sent_letter << setw(size_of_cell) << ToBitString(sent_letter);
            for (char received_letter : receiver_alphabet)
            {
                fout << setw(size_of_cell) << channel_matrix.get(sent_letter).get(received_letter);
            }
            fout << "\n";
        }
        fout << "\n";
        HashMap<Character, Double> probability_to_send = new HashMap<Character, Double>(Map.ofEntries(Map.entry('a', 0.124279), Map.entry('b', 0.039437), Map.entry('c', 0.059650), Map.entry('d', 0.095822), Map.entry('e', 0.319089), Map.entry('f', 0.029545), Map.entry('g', 0.056979), Map.entry('h', 0.093613), Map.entry('i', 0.144755), Map.entry('j', 0.005672), Map.entry('k', 0.031160)));
        HashMap<Character, Double> probability_to_receive = new HashMap<Character, Double>();
        for (char received_letter : receiver_alphabet)
        {
// formula of total probability
            double sum = 0;
            for (char sent_letter : source_alphabet)
            {
                sum += channel_matrix.get(sent_letter).get(received_letter) * probability_to_send.get(sent_letter);
            }
            probability_to_receive.put(received_letter, sum);
        }
        fout << "PROBABILITY TO RECEIVE LETTER:" << "\n";
        for (char letter : receiver_alphabet)
        {
            fout << setw(size_of_cell) << letter << setw(size_of_cell) << probability_to_receive.get(letter) << "\n";
        }
        fout << "\n";
        double receiver_entropy = 0;
        for (char letter : receiver_alphabet)
        {
            receiver_entropy -= probability_to_receive.get(letter) * log2(probability_to_receive.get(letter));
        }
        fout << "RECEIVERS ENTROPY: " << receiver_entropy << "\n";
        System.out.printf("%.8f", "RECEIVERS ENTROPY: ");
        System.out.printf("%.8f", receiver_entropy);
        System.out.printf("%.8f", "\n");
        double noise_entropy = 0;
        for (char sent_letter : source_alphabet)
        {
            double sum = 0;
            for (char received_letter : receiver_alphabet)
            {
                sum += channel_matrix.get(sent_letter).get(received_letter) * log2(channel_matrix.get(sent_letter).get(received_letter));
            }
            noise_entropy -= sum * probability_to_send.get(sent_letter);
        }
        System.out.printf("%.8f", "NOISE ENTROPY: ");
        System.out.printf("%.8f", noise_entropy);
        System.out.printf("%.8f", "\n");
        fout << "NOISE ENTROPY: " << noise_entropy << "\n";
        double leak_entropy = 0;
        for (char received_letter : receiver_alphabet)
        {
            double sum = 0;
            for (char sent_letter : source_alphabet)
            {
                double tmp = channel_matrix.get(sent_letter).get(received_letter) * probability_to_send.get(sent_letter) / probability_to_receive.get(received_letter);
                sum += tmp * log2(tmp);
            }
            leak_entropy -= sum * probability_to_receive.get(received_letter);
        }
        System.out.print("LEAK ENTROPY: ");
        System.out.print(leak_entropy);
        System.out.print("\n");
        fout << "LEAK ENTROPY: " << leak_entropy << "\n";
    }
            }


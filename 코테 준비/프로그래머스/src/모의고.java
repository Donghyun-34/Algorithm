import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;

class Solution {
    public int[] solution(int[] answers) {
        int[] first_peo = {1, 2, 3, 4, 5};
        int[] second_peo = {2, 1, 2, 3, 2, 4, 2, 5};
        int[] third_peo = {3, 3, 1, 1, 2, 2, 4, 4, 5, 5};
        int ans_len = answers.length;
        ArrayList<Integer> score = new ArrayList<>(Arrays.asList(0, 0, 0));

        for(int i =0; i<ans_len; i++){
            if(answers[i] == first_peo[i % first_peo.length])
                score.set(0, score.get(0)+1);
            if(answers[i] == second_peo[i % second_peo.length])
                score.set(1, score.get(1)+1);
            if (answers[i] == third_peo[i % third_peo.length])
                score.set(2, score.get(2)+1);
        }

        int max = Collections.max(score);

        ArrayList<Integer> tempAnswer = new ArrayList<>();

        for (int i = 0; i < score.size(); i++) {
            if (score.get(i) == max) {
                tempAnswer.add(i+1);
            }
        }

        Collections.sort(tempAnswer);

        int[] answer = new int[tempAnswer.size()];
        for(int i = 0; i < tempAnswer.size(); i++) {
            answer[i] = tempAnswer.get(i);
        }

        Arrays.sort(answer);

        return answer;
    }
}
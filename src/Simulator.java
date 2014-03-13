import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;

public class Simulator {

	static Main GUI;
	static int game[]=new int[82];
	static String player1outputfile="output1";
	static String player2outputfile="output2";
	static String boardFileName="boardFile"; //provide this filename to players
	static String player1bashFile="./player1.sh";
	static String player2bashFile="./player2.sh";
	static int playersChance=1;
		static int previous=0;
public static void main(String args[]) throws IOException, InterruptedException{
		GUI=new Main();
		startGame();
	}
	public static void startGame() throws IOException, InterruptedException{

		while(true){
			changeBoardTextFile();
			int move=getMove();
			//System.out.println("Player "+playersChance+" move:"+move);
			if(game[move]!=0){
				Main.message.setText("Player "+Integer.toString(playersChance)+" Lost. Wrong Move");
				System.out.println("Player "+Integer.toString(playersChance)+" Lost. Wrong Move");
				break;
			}
			else if(isValidMove(move,previous)){

				game[move]=playersChance;
				if(isWinner()){
					Main.message.setText("Player "+Integer.toString(playersChance)+" Wins");
					break;

				}else if(isGameFinished()){
					Main.message.setText("Match Draw");
					break;
				}
				else{
					playersChance=playersChance==1?2:1;
					previous=move;

				}
			}
			else {
				Main.message.setText("Player "+Integer.toString(playersChance)+" Loses");
				break;
			}

		}

	}

	private static int getMove() {
		int move;
		if(playersChance==1)
			move=first_player_move();
		else move=second_player_move();
		return move;
	}

	private static int first_player_move(){
		int move=0;
		try {
			Process process=Runtime.getRuntime().exec(player1bashFile);
			process.waitFor();
			BufferedReader in=new BufferedReader(new FileReader(player1outputfile));
			move=Integer.parseInt(in.readLine());
			in.close();
		} catch (IOException e) {
			e.printStackTrace();
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
		return move;
	}
	private static int second_player_move(){
		int move=0;
		try {
			Process process=Runtime.getRuntime().exec(player2bashFile);
			process.waitFor();
			BufferedReader in=new BufferedReader(new FileReader(player2outputfile));
			move=Integer.parseInt(in.readLine());
			in.close();
		} catch (IOException e) {
			e.printStackTrace();
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
		return move;
	}
	private static boolean isGameFinished() {
		int i=1;
		while(i<game.length){
			if(game[i]==0) return false;
			i++;
		}
		return true;
	}

	private static boolean isgridWinner(int x)
	{
		if(game[x]==playersChance&&game[x]==game[x+10]&&game[x+10]==game[x+20])//body diagonal
			return true;
		if(game[x]==playersChance&&game[x]==game[x+9]&&game[x+9]==game[x+18])
			return true;
		if(game[x]==playersChance&&game[x]==game[x+1]&&game[x+1]==game[x+2])
			return true;
		if(game[x+18]==playersChance&&game[x+2]==game[x+10]&&game[x+10]==game[x+18])//other diagonal
			return true;
		if(game[x+2]==playersChance&&game[x+2]==game[x+11]&&game[x+11]==game[x+20])
			return true;
		if(game[x+1]==playersChance&&game[x+1]==game[x+10]&&game[x+10]==game[x+19])
			return true;
		if(game[x+9]==playersChance&&game[x+9]==game[x+10]&&game[x+10]==game[x+11])
			return true;
		if(game[x+18]==playersChance&&game[x+18]==game[x+19]&&game[x+19]==game[x+20])
			return true;
		return false;
	}
	private static boolean isWinner() {
		if(isgridWinner(1)&&isgridWinner(28)&&isgridWinner(55))
			return true;
		if(isgridWinner(1)&&isgridWinner(4)&&isgridWinner(7))
			return true;
		if(isgridWinner(1)&&isgridWinner(31)&&isgridWinner(61))//body diagonal
			return true;
		if(isgridWinner(28)&&isgridWinner(31)&&isgridWinner(58))
			return true;
		if(isgridWinner(4)&&isgridWinner(31)&&isgridWinner(58))
			return true;
		if(isgridWinner(7)&&isgridWinner(34)&&isgridWinner(61))
			return true;
		if(isgridWinner(7)&&isgridWinner(31)&&isgridWinner(55))//other diagonal
			return true;
		if(isgridWinner(55)&&isgridWinner(58)&&isgridWinner(61))
			return true;
		return false;
	}


	private static void changeBoardTextFile() throws IOException {
		FileWriter boardout=new FileWriter(boardFileName);
		BufferedWriter bw = new BufferedWriter(boardout);
		int i=1;
		while(i<game.length){
			try {
				bw.write(Integer.toString(game[i])+" ");
				if(i%9==0) bw.write("\n");
				i++;
				if(i==game.length) bw.write(Integer.toString(playersChance)+" "+Integer.toString(previous) + " \n");
			} catch (IOException e) {
				e.printStackTrace();
				break;
			}

		}


		changeBoard();
		bw.close();

	}
	private static int geti(int box)        //Get row of topleft cell of box
    {
        int i;
        switch((int)(box-1)/3)
        {
            case 0:
                i=1;
                break;
            case 1:
                i=4;
                break;
            case 2:
                i=7;
                break;
            default:
                i=0;
                break;
        }
        return i;
    }
    private static int getj(int box)        //Get column of topleft cell of box
    {
        int j;
        switch(box%3)
        {
            case 0:
                j=7;
                break;
            case 1:
                j=1;
                break;
            case 2:
                j=4;
                break;
            default:
                j=0;
                break;
        }
        return j;
    }
	private static boolean check_box_full(int box)
    {
        int i,j;
        i = geti(box);
        j = getj(box);
        int row, col;
        for(row=i;row<i+3;row++)
            for(col=j;col<j+3;col++)
                if(game[(row-1)*9 + col]==0)
                    return false;
        return true;
    }

	private static void changeBoard()
	{
		for (int i = 1 ;i <= 81; i++)
        {
			if(game[i]!=0)
				Main.game_jLabel[i].setText(Integer.toString(game[i]));
		}
	}
	private static int cellx(int pos)
    {
        return (pos-1)/9 + 1;
    }
    private static int celly(int pos)
    {
        if(pos%9==0)
            return 9;
        return pos%9;
    }

    private static int directedbox(int pos)
    {
        int i = cellx(pos);
        int j = celly(pos);
        if(i%3==1)
        {
            if(j%3==1)
                return 1;
            else if(j%3==2)
                return 2;
            else
                return 3;
        }
        else if(i%3==2)
        {
            if(j%3==1)
                return 4;
            else if(j%3==2)
                return 5;
            else
                return 6;
        }
        else
        {
            if(j%3==1)
                return 7;
            else if(j%3==2)
                return 8;
            else
                return 9;
        }
    }
    private static int getbox(int pos)
    {
        int i = cellx(pos);
        int j = celly(pos);
        if(i>0 && i<4 && j>0 && j<4)
            return 1;
        else if(i>3 && i<7 && j>0 && j<4)
            return 4;
        else if(i>6 && i<10 && j>0 && j<4)
            return 7;
        else if(i>0 && i<4 && j>3 && j<7)
            return 2;
        else if(i>3 && i<7 && j>3 && j<7)
            return 5;
        else if(i>6 && i<10 && j>3 && j<7)
            return 8;
        else if(i>0 && i<4 && j>6 && j<10)
            return 3;
        else if(i>3 && i<7 && j>6 && j<10)
            return 6;
        else if(i>6 && i<10 && j>6 && j<10)
            return 9;
        else
            return 10;
    }
	private static boolean isValidMove(int move, int previous)
	{
	    if(move<1 || move>81)
            return false;
	    if(previous==0)
            return true;
		int box = directedbox(previous);
		if(check_box_full(box))
        {
            if(game[move]==0)
                return true;
            else return false;
        }
        else
        {
            if(getbox(move)==box)
            {
                if(game[move]==0)
                    return true;
                return false;
            }
            else
                return false;
        }
	}
}

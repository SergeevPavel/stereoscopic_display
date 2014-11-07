using UnityEngine;
using System.Collections;

public class FearLevelControl : MonoBehaviour {
	public static bool isSpoted = false;
	public double MaxFearLevel = 100;
	public double CurrentFearLevel = 0;
	public static GameState state;
	public int FearIncr = 2;
	public enum GameState{
		Win,
		Loose,
		InGame,
	}
	// Use this for initialization
	void Start () {
		state = GameState.InGame;
	}

	
	// Update is called once per frame
	void Update () {
		if (state == GameState.InGame)
		{
			if ( isSpoted)
			{
				CurrentFearLevel += FearIncr * Time.deltaTime;
				if (CurrentFearLevel >= MaxFearLevel )
				{
					state = GameState.Loose;
				}
			}
			else
			{
				if ( CurrentFearLevel > 0 )
				{
					CurrentFearLevel -= FearIncr / 2 * Time.deltaTime;
				}
				else
				{
					CurrentFearLevel = 0;
				}
			}
		}
	}

	void OnGUI() 
	{
		if (state == GameState.Loose) 
		{
			GUI.Label(new Rect(Screen.width / 2, Screen.height / 2, 100, 40), "YOU LOSE");
		}
		if (state == GameState.Win)
		{
			GUI.Label(new Rect(Screen.width / 2, Screen.height / 2, 100, 40), "YOU WIN");
		}
		GUI.Label(new Rect(10, 40, 100, 20), ((int)CurrentFearLevel).ToString());
	}
}

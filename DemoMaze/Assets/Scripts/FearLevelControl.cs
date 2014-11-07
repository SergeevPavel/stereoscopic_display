using UnityEngine;
using System.Collections;

public class FearLevelControl : MonoBehaviour {
	public static bool isSpoted = false;
	public float MaxFearLevel = 100;
	public float CurrentFearLevel = 0;
	private Texture2D texture;
	public static GameState state;
	public float FearIncr = 2;
	public enum GameState{
		Win,
		Loose,
		InGame,
	}
	// Use this for initialization
	void Start () {
		texture = new Texture2D(1, 1);
		texture.SetPixel(0,0,Color.gray);
		texture.Apply();
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
					CurrentFearLevel -= FearIncr / 4 * Time.deltaTime;
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
		GUI.skin.box.normal.background = texture;
		GUI.Box(new Rect(Screen.width / 2 - (CurrentFearLevel + 10) * 2.5f / 2, Screen.height - 20, (CurrentFearLevel + 10) * 2.5f, 7), 
		        CurrentFearLevel.ToString() + "/" + MaxFearLevel.ToString());
	}
	
}
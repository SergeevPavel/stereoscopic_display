using UnityEngine;
using System.Collections;

public class WinDetection : MonoBehaviour {

	// Use this for initialization
	void Start () {
	
	}
	
	// Update is called once per frame
	void Update () {
	
	}

	void OnTriggerEnter(Collider other) {
		if (other.gameObject.tag == "Player" && FearLevelControl.state == FearLevelControl.GameState.InGame)
			FearLevelControl.state = FearLevelControl.GameState.Win;
	}
}

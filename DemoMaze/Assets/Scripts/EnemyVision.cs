using UnityEngine;
using System.Collections;
using System;
using System.Runtime.InteropServices;

public class EnemyVision : MonoBehaviour {
	public float angle = 110f;
	public float visionDistance = 40f;
	private GameObject player;
	// Use this for initialization
	void Start () {
		player = GameObject.FindGameObjectWithTag ("Player");
	}
	
	// Update is called once per frame
	void Update () {
		if (Vector3.Angle( transform.position, player.transform.position) <= angle)
		{
			if (Vector3.Distance (transform.position, player.transform.position) <= 40f)
			{
			    FearLevelControl.isSpoted = true;
			}
			else
			{
				FearLevelControl.isSpoted = false;
			}
		}
		else
		{
			FearLevelControl.isSpoted = false;
		}
	}
}

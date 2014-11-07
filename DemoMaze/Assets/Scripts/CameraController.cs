using UnityEngine;
using System.Collections;
using System.Runtime.InteropServices;
using System.IO;
using System.Diagnostics;
using System;

public class CameraController : MonoBehaviour {

	[DllImport("Controller")]
	private static extern int initController();
	[DllImport("Controller")]
	private static extern int deinitController();
	[DllImport("Controller")]
	private static extern float getVerticalAngle();
	[DllImport("Controller")]
	private static extern float getHorizontalAngle();

	[DllImport("kernel32", SetLastError=true)]
	static extern bool FreeLibrary(IntPtr hModule);
	[DllImport("kernel32", SetLastError=true)]
	static extern IntPtr GetModuleHandle(string ModuleName);

	public int rotation = 50;
	public int maxAngle = 50;
	public float delta = 0.1f;
	private GameObject leader;
	private GameObject player;
	private float currentAngle = 0;
	private float prevAngle = 0;
	
	// Use this for initialization
	void Start () {
		initController ();
		leader = GameObject.FindGameObjectWithTag("Leader");
		player = GameObject.FindGameObjectWithTag ("Player");
		currentAngle = 0;
	}
	
	// Update is called once per frame
	void Update () {
		prevAngle = currentAngle;
		currentAngle = getHorizontalAngle () * maxAngle;
		if (Math.Abs (currentAngle - prevAngle) <= delta)
						currentAngle = prevAngle;
		transform.RotateAround(leader.transform.position, leader.transform.up, currentAngle - prevAngle);
		                              
		if (Input.GetKey (KeyCode.Space))
		{
			transform.position = player.transform.position;
			transform.position += transform.forward * 0.18f;
			transform.rotation = player.transform.rotation;
			transform.Rotate(Vector3.up, 90);
			currentAngle = 0;
		}
	}

	void OnApplicationQuit()
	{
		deinitController ();
		FreeLibrary (GetModuleHandle ("Controller"));
	}
}

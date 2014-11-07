using UnityEngine;
using System.Collections;
using System;
using System.Runtime.InteropServices;

public class ObjectController : MonoBehaviour {

	public bool rendered = true;
	public int velocity = 1;
	public int rotation = 45;
	private moveDirection state;
	private enum moveDirection{
		Stop,
		Forward, 
		Backward,
	};

	//use this for initialization
	void Start () {
		renderer.enabled = rendered;
		rigidbody.detectCollisions = true;
		rigidbody.collisionDetectionMode = CollisionDetectionMode.ContinuousDynamic;
	}



	void moveForward ()
	{
		transform.position += transform.right * velocity * Time.deltaTime;
	}
	
	void moveBackward ()
	{
		transform.position -= transform.right * velocity * Time.deltaTime;
	}
	
	void moveLeft ()
	{
		transform.Rotate (Vector3.down * rotation * Time.deltaTime);
	}
	
	void moveRight ()
	{
		transform.Rotate (Vector3.up * rotation * Time.deltaTime);
	}
	
	// Update is called once per frame
	void Update () {
		
		if (Input.GetKeyUp (KeyCode.W) || Input.GetKeyUp (KeyCode.S)) {
			state = moveDirection.Stop;
		}
		
		if (Input.GetKey (KeyCode.W)) {
			state = moveDirection.Forward;
			moveForward ();
		}
		if (Input.GetKey (KeyCode.S)) {
			state = moveDirection.Backward;
			moveBackward();
		}
		if (Input.GetKey( KeyCode.A)) {
			switch( state )
			{
			case moveDirection.Stop: 
				moveLeft();
				break;
			case moveDirection.Forward:
				moveLeft();
				break;
			case moveDirection.Backward:
				moveRight();
				break;
			}
		}
		if (Input.GetKey( KeyCode.D)) {
			switch( state )
			{
			case moveDirection.Stop: 
				moveRight();
				break;
			case moveDirection.Forward:
				moveRight();
				break;
			case moveDirection.Backward:
				moveLeft();
				break;
			}
		}
	}
}
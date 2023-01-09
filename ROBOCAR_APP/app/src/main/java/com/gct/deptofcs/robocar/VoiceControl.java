package com.gct.deptofcs.robocar;
import android.support.v7.app.*;
import android.speech.*;
import android.content.*;
import java.util.*;
import android.os.*;
import android.widget.*;
import android.speech.tts.*;

public class VoiceControl
{
	private Bluetooth blue;
	private AppCompatActivity activity;
	private SpeechRecognizer reco;
	private Intent speechRecognizerIntent;
	private TextToSpeech tts;
	public static boolean IS_LISTENING = false;
	//private CheckBox micButton;
	VoiceControl(AppCompatActivity a,Bluetooth b){
		activity = a;
		blue = b;
		//micButton = btn;
		tts = new TextToSpeech(activity, new TextToSpeech.OnInitListener() { 
			@Override
			public void onInit(int i) { 
				// if No error is found then only it will run 
				if(i!=TextToSpeech.ERROR){  
					// To Choose language of speech 
					tts.setLanguage(Locale.UK);  
				} 
			} 
		}); 
		
		reco = SpeechRecognizer.createSpeechRecognizer(a);
		reco.setRecognitionListener(new RecognitionListener(){
			@Override
			public void onResults(Bundle bundle) {
				ArrayList<String> data = bundle.getStringArrayList(SpeechRecognizer.RESULTS_RECOGNITION);
				if(IS_LISTENING)reco.startListening(speechRecognizerIntent);
				speak(data.get(0));
				Toast.makeText(activity,""+data,2000).show();
			}
			@Override
			public void onBeginningOfSpeech() {
				
			}
			public void onReadyForSpeech(Bundle bundle) {}
			public void onRmsChanged(float v) {}
			public void onBufferReceived(byte[] bytes) {}
			public void onEndOfSpeech() {}
			public void onError(int i) {
				switch(i){
					case SpeechRecognizer.ERROR_AUDIO:
					case SpeechRecognizer.ERROR_NO_MATCH:
						if(IS_LISTENING){
							speak("Say it once more",true);
							reco.startListening(speechRecognizerIntent);
						}
						break;
					case SpeechRecognizer.ERROR_NETWORK:
					case SpeechRecognizer.ERROR_NETWORK_TIMEOUT:
					case SpeechRecognizer.ERROR_SERVER:
						speak("Network error",true);
						break;
					case SpeechRecognizer.ERROR_SPEECH_TIMEOUT:
						if(IS_LISTENING)reco.startListening(speechRecognizerIntent);
						break;
				}
			}
			public void onPartialResults(Bundle bundle) {}
			public void onEvent(int i, Bundle bundle) {
				
			}
			
		});
		speechRecognizerIntent = new Intent(RecognizerIntent.ACTION_RECOGNIZE_SPEECH);
		speechRecognizerIntent.putExtra(RecognizerIntent.EXTRA_LANGUAGE_MODEL,RecognizerIntent.LANGUAGE_MODEL_FREE_FORM);
		speechRecognizerIntent.putExtra(RecognizerIntent.EXTRA_LANGUAGE, Locale.getDefault());
	}
	
	public void startListening(){
		//Toast.makeText(activity,"Listening...",2000).show();
		reco.startListening(speechRecognizerIntent);
		IS_LISTENING=true;
		speak("Started Listening",true);
	}
	public void stopListening(){
		//Toast.makeText(activity,"Stoping...",2000).show();
		reco.stopListening();
		IS_LISTENING = false;
		speak("Stoped Listening",true);
	}
	public void speak(String s,boolean b){
		tts.speak(s,TextToSpeech.QUEUE_FLUSH,null);
		if(b) Toast.makeText(activity,s,2000).show();
	}
	public void speak(String s){
		tts.speak(s,TextToSpeech.QUEUE_FLUSH,null);
	}
}

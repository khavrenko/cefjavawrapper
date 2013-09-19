// Copyright (c) 2013 Agitech http://agitech.net, LLC. All rights reserved. Use of this source
// Contributor Nassim MOUALEK nmoualek@agitech.net, agitechs@gmail.com
// code is governed by a BSD-style license that can be found in the LICENSE file.

package org.limewire.cef;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.Font;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.GridLayout;
import java.awt.Menu;
import java.awt.MenuBar;
import java.awt.MenuItem;
import java.awt.Rectangle;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.WindowEvent;
import java.awt.event.WindowListener;
import java.io.File;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Timer;
import java.util.TimerTask;

import javax.swing.Box;
import javax.swing.BoxLayout;
import javax.swing.JButton;
import javax.swing.JFileChooser;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JSlider;
import javax.swing.JTextField;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;
// private code
public class MultiViewFrame extends JFrame implements WindowListener{
	private List<CefBrowser> browsers = new ArrayList<CefBrowser>();
	private JPanel browserPanel;
	private JTextField addressTextField;
	private JTextField nbrPlayerTextField;	
	private Map<JTextField, CefBrowser> jsTextFieldToBrowser = new HashMap<JTextField, CefBrowser>();
	private Map<CefBrowser, JTextField> browserToTextField = new HashMap<CefBrowser, JTextField>();	 
	private int currentPos = 6;
	private double zoomSize = 20.0;
	Timer zoomTaks;
	public MultiViewFrame(boolean initialise) {
		// Initialize the CEF context.
		if (initialise){
			setTitle("Multi-View");			
			setDefaultCloseOperation(EXIT_ON_CLOSE);				
			addWindowListener(this);
			JPanel contentPanel = new JPanel(new BorderLayout());		
			JPanel ctrlPanel = createControlPanel();
			contentPanel.add(ctrlPanel, BorderLayout.NORTH);
			browserPanel = new JPanel();
			browserPanel.setBackground(Color.blue);
			browserPanel.setSize(800, 600);
			contentPanel.add( browserPanel, BorderLayout.CENTER);
			createBrowsers();		
			setContentPane(contentPanel);
		}
		CefContext.initialize("k:/cef_cache");		
	}
		
	protected void finalize() throws Throwable
    {
    	super.finalize();
    }

	
	private JPanel createBrowserPanel(int i) {
		JPanel browserPanel = new JPanel(new BorderLayout());
		//JPanel scriptPanel = new JPanel();
		
		// Create a new CEF browser window.
		JTextField jsTextField = new JTextField(100);
		jsTextField.setText("simul('player"+(i+1)+"');");
		jsTextField.setAlignmentX(LEFT_ALIGNMENT);
		jsTextField.setFont(new Font(null, Font.BOLD, 12));
		jsTextField.addActionListener(new ActionListener() {			
			@Override
			public void actionPerformed(ActionEvent e) {
				JTextField jsTextField = (JTextField)e.getSource();
				jsTextFieldToBrowser.get(jsTextField).getMainFrame().executeJavaScript(jsTextField.getText(), 
						"", 0);
				
			}
		});
		
		browserPanel.add( jsTextField, BorderLayout.SOUTH);
		
		CefBrowser br = CefContext.createBrowser(new MainHandler(null), addressTextField.getText());
		browsers.add( br );
		jsTextFieldToBrowser.put(jsTextField, br);
		browserToTextField.put(br, jsTextField);
		TimerTask task = new TimerTask() {			
			@Override
			public void run() {
				zoomTaks.cancel();
				zoom((currentPos-(zoomSize/2)));
			}
		};		
		zoomTaks = new Timer();
		zoomTaks.schedule(task, 10000);		
		browserPanel.add(br, BorderLayout.CENTER);
				
		return browserPanel;
	}
	private void createBrowsers(){		
		destroyBrowsers();
		jsTextFieldToBrowser.clear();
		browserToTextField.clear();
		browsers.clear();
		browserPanel.setLayout( new GridBagLayout() );
		browserPanel.removeAll();
		GridBagConstraints gbc = new GridBagConstraints();
		gbc.weightx = 1;
		gbc.weighty = 1;
        gbc.anchor = GridBagConstraints.FIRST_LINE_START;
        gbc.fill = GridBagConstraints.BOTH;                
		int nbrPlayers = Integer.parseInt( nbrPlayerTextField.getText() );
		//browserPanel.setLayout(new BoxLayout(browserPanel, BoxLayout.X_AXIS));
		for (int i=0;i<nbrPlayers;i++) {
			JPanel p = createBrowserPanel(i);
			gbc.gridx = i%3;
			gbc.gridy = i/3;
			browserPanel.add( p, gbc);			
		}		
	}
	
	private JPanel createControlPanel() {
		JPanel controlPanel = new JPanel();
		controlPanel.setLayout(new BoxLayout(controlPanel, BoxLayout.X_AXIS));

        controlPanel.add(Box.createHorizontalStrut(5));

        JLabel nbrPlayerLabel = new JLabel("NbrPlayer:");
        nbrPlayerLabel.setAlignmentX(LEFT_ALIGNMENT);
		controlPanel.add(nbrPlayerLabel);

        controlPanel.add(Box.createHorizontalStrut(5));
        
		nbrPlayerTextField = new JTextField(10);
		nbrPlayerTextField.setText("6");
		nbrPlayerTextField.setAlignmentX(LEFT_ALIGNMENT);
		controlPanel.add(nbrPlayerTextField);
		
		JLabel addressLabel = new JLabel("Address:");
		addressLabel.setAlignmentX(LEFT_ALIGNMENT);
		controlPanel.add(addressLabel);

        controlPanel.add(Box.createHorizontalStrut(5));

		addressTextField = new JTextField(100);
		addressTextField.setText("http://localhost:8080/poker/");
		//addressTextField.setText("http://www.google.fr");
		addressTextField.setAlignmentX(LEFT_ALIGNMENT);
		
		controlPanel.add(addressTextField);

        controlPanel.add(Box.createHorizontalStrut(5));

        JButton goButton = new JButton("Create");
		goButton.setAlignmentX(LEFT_ALIGNMENT);
		goButton.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				createBrowsers();
			}
		});
		controlPanel.add(goButton);

        controlPanel.add(Box.createHorizontalStrut(5));
        
        JSlider zoomSlide = new JSlider(JSlider.HORIZONTAL, 1, (int)zoomSize, currentPos);
        controlPanel.add(zoomSlide);
        
        zoomSlide.addChangeListener(new ChangeListener() {		
			@Override
			public void stateChanged(ChangeEvent e) {
				// TODO Auto-generated method stub
				JSlider source = (JSlider)e.getSource();				
				//System.out.println("zoom : "+zoom);
				zoom(source.getValue()-zoomSize/2);
			}
		});
        controlPanel.add(Box.createHorizontalStrut(5));
        JButton execJsButton = new JButton();
        execJsButton.setText("Exec JS");
        execJsButton.addActionListener(new ActionListener() {			
			@Override
			public void actionPerformed(ActionEvent e) {
				for (CefBrowser b: browsers){					
					b.getMainFrame().executeJavaScript( browserToTextField.get(b).getText(), "", 0);
				}
			}
		});
        controlPanel.add(execJsButton);
        controlPanel.add(Box.createHorizontalStrut(5));
		return controlPanel;
	}
	public void zoom(double zoom){
		for (CefBrowser b : browsers){
			b.zoom(zoom);
			//((JPanel)b.getParent()).setAutoscrolls(false);
		}
	}
	public void setAddress(String url)
	{
		addressTextField.setText(url);
	}

	@Override
	public void windowOpened(WindowEvent e) {
		// TODO Auto-generated method stub
		
	}
	public void destroyBrowsers(){
		for (CefBrowser cb : browsers)						
			cb.destroy();		
	}
	@Override
	public void windowClosing(WindowEvent e) {
		
		destroyBrowsers();
		new Thread(new Runnable(){
	        @Override
	        public void run() {
	            Main.queue.add(new Runnable(){
	                @Override
	                public void run() {
	                	System.out.println("Shutting down on thread_id "+Thread.currentThread().getId()+" "+Thread.currentThread().getName());
	                	CefContext.shutdown();
	                	dispose();
	                }
	            });
	        }
	    }).start();
		
	}

	@Override
	public void windowClosed(WindowEvent e) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void windowIconified(WindowEvent e) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void windowDeiconified(WindowEvent e) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void windowActivated(WindowEvent e) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void windowDeactivated(WindowEvent e) {
		// TODO Auto-generated method stub
		
	}
}

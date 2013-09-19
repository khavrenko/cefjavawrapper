// Copyright (c) 2010 Lime Wire, LLC. All rights reserved. Use of this source
// Copyright (c) 2013 Agitech http://agitech.net, LLC. All rights reserved. Use of this source
// Contributor Nassim MOUALEK nmoualek@agitech.net, agitechs@gmail.com
// code is governed by a BSD-style license that can be found in the LICENSE file.


package org.limewire.cef;

import java.io.File;
import java.io.IOException;
import java.lang.management.ManagementFactory;
import java.lang.management.RuntimeMXBean;
import java.util.List;
import java.util.concurrent.BlockingQueue;
import java.util.concurrent.LinkedBlockingQueue;
import javax.swing.JFrame;
import com.sun.akuma.*;
import com.sun.xml.internal.bind.v2.runtime.output.ForkXmlOutput;
public class Main {
	public static final BlockingQueue<Runnable> queue = new LinkedBlockingQueue<Runnable>();
	public static void main(String[] arguments)
	{
		//MainFrame mainFrame = new MainFrame();
		boolean stub = false;
		for (String a : arguments){
			System.out.print(a);
			if (a.contains("stub"))
				stub = true;
		}
		
			MultiViewFrame mainFrame = new MultiViewFrame(!stub);
			mainFrame.setLocation(100, 100);
			mainFrame.setSize(1000, 700);
			mainFrame.setVisible(true);	
			mainFrame.setExtendedState(JFrame.MAXIMIZED_BOTH);
		
		/* Uncomment to prevent closing exception
		while(true) {
	        try {
				queue.take().run();
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
	    }
	    */
	}
}

// Copyright (c) 2010 Lime Wire, LLC. All rights reserved. Use of this source
// Copyright (c) 2013 Agitech http://agitech.net, LLC. All rights reserved. Use of this source
// Contributor Nassim MOUALEK nmoualek@agitech.net, agitechs@gmail.com
// code is governed by a BSD-style license that can be found in the LICENSE file.

package org.limewire.cef;
import java.awt.Frame;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import java.util.logging.Logger;

public class WindowHandleGetter {
    private final Object rootFrame;

    protected WindowHandleGetter(Object rootFrame) {
        this.rootFrame = rootFrame;
    }

    protected long getWindowId() {

        try {
            Object frame = rootFrame;

            // The reflection code below does the same as this
            // long handle = frame.getPeer() != null ? ((WComponentPeer) frame.getPeer()).getHWnd() : 0;

            Object wComponentPeer = invokeMethod(frame, "getPeer");

            Long hwnd = (Long) invokeMethod(wComponentPeer, "getHWnd");

            return hwnd;

        } catch (Exception ex) {
        	
        }

        return 0;
    }
    protected Object invokeMethod(Object o, String methodName) throws IllegalAccessException, IllegalArgumentException, InvocationTargetException {

        Class c = o.getClass();
        for (Method m : c.getMethods()) {
            if (m.getName().equals(methodName)) {
                Object ret = m.invoke(o);
                return ret;
            }
        }
        throw new RuntimeException("Could not find method named '"+methodName+"' on class " + c);

    }
}

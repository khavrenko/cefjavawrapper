// Copyright (c) 2010 Lime Wire, LLC. All rights reserved. Use of this source
// Copyright (c) 2013 Agitech http://agitech.net, LLC. All rights reserved. Use of this source
// Contributor Nassim MOUALEK nmoualek@agitech.net, agitechs@gmail.com
// code is governed by a BSD-style license that can be found in the LICENSE file.

package org.limewire.cef;

public interface CefV8Handler {
	/**
	 * Callback that will be called when the function is executed.
	 * @param name Name of the executed function.
	 * @param params Input and output parameters.
	 * @return True if execution succeeded.
	*/
	public boolean executeFunction(String name, CefV8FunctionParams params);
}

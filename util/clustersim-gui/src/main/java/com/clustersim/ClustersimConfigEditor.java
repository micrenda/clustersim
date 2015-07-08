package com.clustersim;

import java.awt.EventQueue;
import java.io.File;
import java.io.IOException;

import javax.swing.JFileChooser;
import javax.swing.JOptionPane;

import org.apache.commons.lang3.exception.ExceptionUtils;
import org.libconfig.parser.ParseException;


public class ClustersimConfigEditor {

	public static void main(final String[] args) throws ParseException, IOException {

		final File selectedFile;
		
		if (args.length == 0)
		{
			JFileChooser fc = new JFileChooser(new File("config"));
			int returnVal = fc.showOpenDialog(null);
			
			if (returnVal == JFileChooser.APPROVE_OPTION)
			{
				selectedFile = fc.getSelectedFile();
			}
			else
				selectedFile = null;
		}
		else
			selectedFile = new File(args[0]);
		
		if (selectedFile != null)
		{
		EventQueue.invokeLater(new Runnable() 
		{
			public void run()
			{
				try
				{
					new MainForm(selectedFile);
				} catch (Exception e)
				{
					JOptionPane.showMessageDialog(null, ExceptionUtils.getStackTrace(e), "Error", JOptionPane.ERROR_MESSAGE);
					e.printStackTrace();
				}
			}
		});
		}
	}
}

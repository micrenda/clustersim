package com.clustersim;

import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.Insets;
import java.awt.event.FocusAdapter;
import java.awt.event.FocusEvent;
import java.awt.event.ItemEvent;
import java.awt.event.ItemListener;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.StringReader;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

import javax.swing.DefaultComboBoxModel;
import javax.swing.JButton;
import javax.swing.JCheckBox;
import javax.swing.JComboBox;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JList;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JSpinner;
import javax.swing.JTabbedPane;
import javax.swing.JTextField;
import javax.swing.JTextPane;
import javax.swing.SwingConstants;
import javax.swing.border.EmptyBorder;
import javax.swing.border.TitledBorder;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;

import org.apache.commons.lang3.StringUtils;
import org.jdesktop.beansbinding.AutoBinding;
import org.jdesktop.beansbinding.AutoBinding.UpdateStrategy;
import org.jdesktop.beansbinding.BeanProperty;
import org.jdesktop.beansbinding.Bindings;
import org.jdesktop.beansbinding.Converter;
import org.jdesktop.beansbinding.ELProperty;
import org.jdesktop.beansbinding.Validator;
import org.libconfig.Config;
import org.libconfig.ConfigOutputter;
import org.libconfig.Setting;
import org.libconfig.parser.ConfigParser;
import org.libconfig.parser.ParseException;

@SuppressWarnings("rawtypes")
public class MainForm extends JFrame {
	
	private static final long serialVersionUID = 3757427787703655561L;
	
	private JPanel contentPane;
	private JTextField fieldBasename;
	private JComboBox<String> comboDimensionality;
	private JTabbedPane tabbedPane;
	private JPanel panel;
	private JLabel lblDuration;
	private JTextField fieldDuration;
	private JLabel lblContainerSize;
	private JLabel lblStopWhenVolume;
	private JTextField textField;
	private JTextField textField_2;
	private JLabel lblFitJmakCoeff;
	private JLabel lblAnd;
	private JTextField textField_3;
	private JPanel panel_2;
	private JPanel panel_3;
	private JPanel panel_4;
	private JPanel panel_5;
	private JPanel panel_6;
	private JPanel panel_1;
	private JTextPane textPane;
	private JTextPane textPane_1;
	private JTextPane textPane_2;
	private JTextPane textPane_3;
	private JCheckBox ckThreads;
	private JLabel lblUseUpTo;
	private JSpinner textField_1;
	private JLabel lblThreads;
	private JCheckBox ckRepeat;
	private JLabel lblRepeat;
	private JSpinner textField_4;
	private JLabel lblTimes;
	private JCheckBox ckDebug;
	private JLabel lblShowDebugMessages;
	private JCheckBox ckEncoder;
	private JLabel lblUse;
	private JComboBox<String> comboBox;
	private JLabel lblEncoder;
	private JCheckBox ckKeepPNG;
	private JLabel lblKeepPngs;
	private JCheckBox ckOutputDir;
	private JLabel lblOutputDir;
	private JTextField textField_5;
	private JCheckBox ckUseShortArgs;
	private JLabel lblNewLabel;
	private JTextPane textPane_4;
	private JLabel lblLaunchCommand;
	private JCheckBox ckGeneralPosition;
	
	private CmdLineLauncher cmdLineLauncher = new CmdLineLauncher();
	private SimulationConfig simulation;
	
	private int currentSelectedPositionFunc;
	private JLabel lblFile;
	private JTextField textField_6;

	private File file;
	
	
	protected void getPositionFuncsLabels(List<String> values)
	{
		
	}
	
	protected List<String> getPositionFuncsLabels() {
		ArrayList<String> list = new ArrayList<String>();

		
		if (simulation.isGenericPosition()) {
			list.add("generic axis");
		} else {
			int d = simulation.getDimensionsValue();

			if (d <= 3) {
				if (d >= 1)
					list.add("x-axis");
				if (d >= 2)
					list.add("y-axis");
				if (d >= 3)
					list.add("z-axis");
			} else {
				for (int i = 0; i < d; i++)
					list.add(String.format("r%d-axis", i + 1));
			}

		}
		
		
		return list;
	}
	

	public MainForm() throws FileNotFoundException, ParseException {
		
		this(null);
	}
	/**
	 * Create the frame.
	 * @throws ParseException 
	 * @throws FileNotFoundException 
	 */
	@SuppressWarnings("rawtypes")
	public MainForm(final File file) throws FileNotFoundException, ParseException {
		this.file = file;
		
		this.simulation = loadConfig(file);
		
		
		
		if (simulation == null)
		{
			dispose();
			System.exit(0);
			return;
		}
		
		setTitle("Clustersim Configuration");
		setDefaultCloseOperation(JFrame.DO_NOTHING_ON_CLOSE);
		setBounds(100, 100, 819, 650);
		contentPane = new JPanel();
		contentPane.setBorder(new EmptyBorder(5, 5, 5, 5));
		setContentPane(contentPane);
		GridBagLayout gbl_contentPane = new GridBagLayout();
		gbl_contentPane.columnWidths = new int[]{0, 0, 0, 0, 0};
		gbl_contentPane.rowHeights = new int[]{0, 0, 0, 0};
		gbl_contentPane.columnWeights = new double[]{0.0, 1.0, 0.0, 0.0, Double.MIN_VALUE};
		gbl_contentPane.rowWeights = new double[]{0.0, 0.0, 1.0, Double.MIN_VALUE};
		contentPane.setLayout(gbl_contentPane);
		
		lblFile = new JLabel("File");
		GridBagConstraints gbc_lblFile = new GridBagConstraints();
		gbc_lblFile.anchor = GridBagConstraints.EAST;
		gbc_lblFile.insets = new Insets(0, 0, 5, 5);
		gbc_lblFile.gridx = 0;
		gbc_lblFile.gridy = 0;
		contentPane.add(lblFile, gbc_lblFile);
		
		textField_6 = new JTextField();
		textField_6.setEditable(false);
		GridBagConstraints gbc_textField_6 = new GridBagConstraints();
		gbc_textField_6.gridwidth = 3;
		gbc_textField_6.insets = new Insets(0, 0, 5, 5);
		gbc_textField_6.fill = GridBagConstraints.HORIZONTAL;
		gbc_textField_6.gridx = 1;
		gbc_textField_6.gridy = 0;
		contentPane.add(textField_6, gbc_textField_6);
		textField_6.setColumns(10);
		
		JLabel lblBasename = new JLabel("Basename");
		GridBagConstraints gbc_lblBasename = new GridBagConstraints();
		gbc_lblBasename.insets = new Insets(0, 0, 5, 5);
		gbc_lblBasename.anchor = GridBagConstraints.EAST;
		gbc_lblBasename.gridx = 0;
		gbc_lblBasename.gridy = 1;
		contentPane.add(lblBasename, gbc_lblBasename);
		
		fieldBasename = new JTextField();
		GridBagConstraints gbc_fieldBasename = new GridBagConstraints();
		gbc_fieldBasename.fill = GridBagConstraints.HORIZONTAL;
		gbc_fieldBasename.insets = new Insets(0, 0, 5, 5);
		gbc_fieldBasename.gridx = 1;
		gbc_fieldBasename.gridy = 1;
		contentPane.add(fieldBasename, gbc_fieldBasename);
		fieldBasename.setColumns(10);
		
		JLabel lblDimensionality = new JLabel("Dimensionality");
		GridBagConstraints gbc_lblDimensionality = new GridBagConstraints();
		gbc_lblDimensionality.insets = new Insets(0, 0, 5, 5);
		gbc_lblDimensionality.anchor = GridBagConstraints.EAST;
		gbc_lblDimensionality.gridx = 2;
		gbc_lblDimensionality.gridy = 1;
		contentPane.add(lblDimensionality, gbc_lblDimensionality);
		
		comboDimensionality = new JComboBox<String>();
		comboDimensionality.setModel(new DefaultComboBoxModel<String>(new String[] {"1D", "2D", "3D", "4D", "5D", "6D", "7D", "8D", "9D", "10D", "11D", "12D", "13D", "14D", "15D", "16D", "17D", "18D", "19D", "20D", "21D", "22D", "23D", "24D", "25D", "26D", "27D", "28D", "29D", "30D", "31D", "32D", "33D", "34D", "35D", "36D", "37D", "38D", "39D", "40D", "41D", "42D", "43D", "44D", "45D", "46D", "47D", "48D", "49D", "50D", "51D", "52D", "53D", "54D", "55D", "56D", "57D", "58D", "59D", "60D", "61D", "62D", "63D", "64D", "65D", "66D", "67D", "68D", "69D", "70D", "71D", "72D", "73D", "74D", "75D", "76D", "77D", "78D", "79D", "80D", "81D", "82D", "83D", "84D", "85D", "86D", "87D", "88D", "89D", "90D", "91D", "92D", "93D", "94D", "95D", "96D", "97D", "98D", "99D", "100D", "101D", "102D", "103D", "104D", "105D", "106D", "107D", "108D", "109D", "110D", "111D", "112D", "113D", "114D", "115D", "116D", "117D", "118D", "119D", "120D", "121D", "122D", "123D", "124D", "125D", "126D", "127D", "128D", "129D", "130D", "131D", "132D", "133D", "134D", "135D", "136D", "137D", "138D", "139D", "140D", "141D", "142D", "143D", "144D", "145D", "146D", "147D", "148D", "149D", "150D", "151D", "152D", "153D", "154D", "155D", "156D", "157D", "158D", "159D", "160D", "161D", "162D", "163D", "164D", "165D", "166D", "167D", "168D", "169D", "170D", "171D", "172D", "173D", "174D", "175D", "176D", "177D", "178D", "179D", "180D", "181D", "182D", "183D", "184D", "185D", "186D", "187D", "188D", "189D", "190D", "191D", "192D", "193D", "194D", "195D", "196D", "197D", "198D", "199D", "200D", "201D", "202D", "203D", "204D", "205D", "206D", "207D", "208D", "209D", "210D", "211D", "212D", "213D", "214D", "215D", "216D", "217D", "218D", "219D", "220D", "221D", "222D", "223D", "224D", "225D", "226D", "227D", "228D", "229D", "230D", "231D", "232D", "233D", "234D", "235D", "236D", "237D", "238D", "239D", "240D", "241D", "242D", "243D", "244D", "245D", "246D", "247D", "248D", "249D", "250D", "251D", "252D", "253D", "254D", "255D"}));
		GridBagConstraints gbc_comboDimensionality = new GridBagConstraints();
		gbc_comboDimensionality.anchor = GridBagConstraints.WEST;
		gbc_comboDimensionality.insets = new Insets(0, 0, 5, 0);
		gbc_comboDimensionality.gridx = 3;
		gbc_comboDimensionality.gridy = 1;
		contentPane.add(comboDimensionality, gbc_comboDimensionality);
		
		tabbedPane = new JTabbedPane(JTabbedPane.TOP);
		GridBagConstraints gbc_tabbedPane = new GridBagConstraints();
		gbc_tabbedPane.gridwidth = 4;
		gbc_tabbedPane.fill = GridBagConstraints.BOTH;
		gbc_tabbedPane.gridx = 0;
		gbc_tabbedPane.gridy = 2;
		contentPane.add(tabbedPane, gbc_tabbedPane);
		
		panel = new JPanel();
		tabbedPane.addTab("Main", null, panel, null);
		GridBagLayout gbl_panel = new GridBagLayout();
		gbl_panel.columnWidths = new int[]{0, 0};
		gbl_panel.rowHeights = new int[]{0, 0, 0};
		gbl_panel.columnWeights = new double[]{1.0, Double.MIN_VALUE};
		gbl_panel.rowWeights = new double[]{0.0, 1.0, Double.MIN_VALUE};
		panel.setLayout(gbl_panel);
		
		panel_6 = new JPanel();
		panel_6.setBorder(new TitledBorder(null, "Simulation", TitledBorder.LEADING, TitledBorder.TOP, null, null));
		GridBagConstraints gbc_panel_6 = new GridBagConstraints();
		gbc_panel_6.fill = GridBagConstraints.HORIZONTAL;
		gbc_panel_6.insets = new Insets(0, 0, 5, 0);
		gbc_panel_6.anchor = GridBagConstraints.NORTH;
		gbc_panel_6.gridx = 0;
		gbc_panel_6.gridy = 0;
		panel.add(panel_6, gbc_panel_6);
		GridBagLayout gbl_panel_6 = new GridBagLayout();
		gbl_panel_6.columnWidths = new int[]{62, 114, 50, 0, 0};
		gbl_panel_6.rowHeights = new int[]{19, 0, 0, 0, 0};
		gbl_panel_6.columnWeights = new double[]{0.0, 0.0, 0.0, 1.0, Double.MIN_VALUE};
		gbl_panel_6.rowWeights = new double[]{0.0, 1.0, 0.0, 0.0, Double.MIN_VALUE};
		panel_6.setLayout(gbl_panel_6);
		
		lblDuration = new JLabel("Duration");
		GridBagConstraints gbc_lblDuration = new GridBagConstraints();
		gbc_lblDuration.anchor = GridBagConstraints.EAST;
		gbc_lblDuration.insets = new Insets(0, 0, 5, 5);
		gbc_lblDuration.gridx = 0;
		gbc_lblDuration.gridy = 0;
		panel_6.add(lblDuration, gbc_lblDuration);
		
		fieldDuration = new JTextField();
		GridBagConstraints gbc_fieldDuration = new GridBagConstraints();
		gbc_fieldDuration.insets = new Insets(0, 0, 5, 5);
		gbc_fieldDuration.anchor = GridBagConstraints.NORTHWEST;
		gbc_fieldDuration.gridx = 1;
		gbc_fieldDuration.gridy = 0;
		panel_6.add(fieldDuration, gbc_fieldDuration);
		fieldDuration.setColumns(10);
		
		lblContainerSize = new JLabel("Container size");
		GridBagConstraints gbc_lblContainerSize = new GridBagConstraints();
		gbc_lblContainerSize.anchor = GridBagConstraints.EAST;
		gbc_lblContainerSize.insets = new Insets(0, 0, 5, 5);
		gbc_lblContainerSize.gridx = 0;
		gbc_lblContainerSize.gridy = 1;
		panel_6.add(lblContainerSize, gbc_lblContainerSize);
		
		textField_8 = new JTextField();
		GridBagConstraints gbc_textField_8 = new GridBagConstraints();
		gbc_textField_8.gridwidth = 3;
		gbc_textField_8.insets = new Insets(0, 0, 5, 5);
		gbc_textField_8.fill = GridBagConstraints.HORIZONTAL;
		gbc_textField_8.gridx = 1;
		gbc_textField_8.gridy = 1;
		panel_6.add(textField_8, gbc_textField_8);
		textField_8.setColumns(10);
		
		lblStopWhenVolume = new JLabel("Stop when volume is");
		GridBagConstraints gbc_lblStopWhenVolume = new GridBagConstraints();
		gbc_lblStopWhenVolume.anchor = GridBagConstraints.EAST;
		gbc_lblStopWhenVolume.insets = new Insets(0, 0, 5, 5);
		gbc_lblStopWhenVolume.gridx = 0;
		gbc_lblStopWhenVolume.gridy = 2;
		panel_6.add(lblStopWhenVolume, gbc_lblStopWhenVolume);
		
		textField = new JTextField();
		GridBagConstraints gbc_textField = new GridBagConstraints();
		gbc_textField.anchor = GridBagConstraints.WEST;
		gbc_textField.insets = new Insets(0, 0, 5, 5);
		gbc_textField.gridx = 1;
		gbc_textField.gridy = 2;
		panel_6.add(textField, gbc_textField);
		textField.setColumns(10);
		
		lblFitJmakCoeff = new JLabel("Fit JMAK between");
		GridBagConstraints gbc_lblFitJmakCoeff = new GridBagConstraints();
		gbc_lblFitJmakCoeff.anchor = GridBagConstraints.EAST;
		gbc_lblFitJmakCoeff.insets = new Insets(0, 0, 0, 5);
		gbc_lblFitJmakCoeff.gridx = 0;
		gbc_lblFitJmakCoeff.gridy = 3;
		panel_6.add(lblFitJmakCoeff, gbc_lblFitJmakCoeff);
		
		textField_2 = new JTextField();
		GridBagConstraints gbc_textField_2 = new GridBagConstraints();
		gbc_textField_2.anchor = GridBagConstraints.WEST;
		gbc_textField_2.insets = new Insets(0, 0, 0, 5);
		gbc_textField_2.gridx = 1;
		gbc_textField_2.gridy = 3;
		panel_6.add(textField_2, gbc_textField_2);
		textField_2.setColumns(10);
		
		lblAnd = new JLabel("and");
		GridBagConstraints gbc_lblAnd = new GridBagConstraints();
		gbc_lblAnd.insets = new Insets(0, 0, 0, 5);
		gbc_lblAnd.gridx = 2;
		gbc_lblAnd.gridy = 3;
		panel_6.add(lblAnd, gbc_lblAnd);
		
		textField_3 = new JTextField();
		GridBagConstraints gbc_textField_3 = new GridBagConstraints();
		gbc_textField_3.anchor = GridBagConstraints.WEST;
		gbc_textField_3.gridx = 3;
		gbc_textField_3.gridy = 3;
		panel_6.add(textField_3, gbc_textField_3);
		textField_3.setColumns(10);
		
		panel_1 = new JPanel();
		panel_1.setBorder(new TitledBorder(null, "Execution", TitledBorder.LEADING, TitledBorder.TOP, null, null));
		GridBagConstraints gbc_panel_1 = new GridBagConstraints();
		gbc_panel_1.fill = GridBagConstraints.BOTH;
		gbc_panel_1.gridx = 0;
		gbc_panel_1.gridy = 1;
		panel.add(panel_1, gbc_panel_1);
		GridBagLayout gbl_panel_1 = new GridBagLayout();
		gbl_panel_1.columnWidths = new int[]{0, 0, 0, 0, 0, 0};
		gbl_panel_1.rowHeights = new int[]{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
		gbl_panel_1.columnWeights = new double[]{0.0, 0.0, 0.0, 1.0, 0.0, Double.MIN_VALUE};
		gbl_panel_1.rowWeights = new double[]{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, Double.MIN_VALUE};
		panel_1.setLayout(gbl_panel_1);
		 
		ckThreads = new JCheckBox("");
		GridBagConstraints gbc_ckThreads = new GridBagConstraints();
		gbc_ckThreads.insets = new Insets(0, 0, 5, 5);
		gbc_ckThreads.gridx = 0;
		gbc_ckThreads.gridy = 0;
		panel_1.add(ckThreads, gbc_ckThreads);
		
		lblUseUpTo = new JLabel("use up to");
		GridBagConstraints gbc_lblUseUpTo = new GridBagConstraints();
		gbc_lblUseUpTo.insets = new Insets(0, 0, 5, 5);
		gbc_lblUseUpTo.anchor = GridBagConstraints.WEST;
		gbc_lblUseUpTo.gridx = 1;
		gbc_lblUseUpTo.gridy = 0;
		panel_1.add(lblUseUpTo, gbc_lblUseUpTo);
		
		textField_1 = new JSpinner();
		GridBagConstraints gbc_textField_1 = new GridBagConstraints();
		gbc_textField_1.insets = new Insets(0, 0, 5, 5);
		gbc_textField_1.fill = GridBagConstraints.HORIZONTAL;
		gbc_textField_1.gridx = 2;
		gbc_textField_1.gridy = 0;
		panel_1.add(textField_1, gbc_textField_1);
		
		lblThreads = new JLabel("threads");
		GridBagConstraints gbc_lblThreads = new GridBagConstraints();
		gbc_lblThreads.anchor = GridBagConstraints.WEST;
		gbc_lblThreads.insets = new Insets(0, 0, 5, 5);
		gbc_lblThreads.gridx = 3;
		gbc_lblThreads.gridy = 0;
		panel_1.add(lblThreads, gbc_lblThreads);
		
		ckRepeat = new JCheckBox("");
		GridBagConstraints gbc_ckRepeat = new GridBagConstraints();
		gbc_ckRepeat.insets = new Insets(0, 0, 5, 5);
		gbc_ckRepeat.gridx = 0;
		gbc_ckRepeat.gridy = 1;
		panel_1.add(ckRepeat, gbc_ckRepeat);
		
		lblRepeat = new JLabel("repeat");
		GridBagConstraints gbc_lblRepeat = new GridBagConstraints();
		gbc_lblRepeat.anchor = GridBagConstraints.WEST;
		gbc_lblRepeat.insets = new Insets(0, 0, 5, 5);
		gbc_lblRepeat.gridx = 1;
		gbc_lblRepeat.gridy = 1;
		panel_1.add(lblRepeat, gbc_lblRepeat);
		
		textField_4 = new JSpinner();
		GridBagConstraints gbc_textField_4 = new GridBagConstraints();
		gbc_textField_4.insets = new Insets(0, 0, 5, 5);
		gbc_textField_4.fill = GridBagConstraints.HORIZONTAL;
		gbc_textField_4.gridx = 2;
		gbc_textField_4.gridy = 1;
		panel_1.add(textField_4, gbc_textField_4);
		
		lblTimes = new JLabel("times");
		GridBagConstraints gbc_lblTimes = new GridBagConstraints();
		gbc_lblTimes.insets = new Insets(0, 0, 5, 5);
		gbc_lblTimes.anchor = GridBagConstraints.WEST;
		gbc_lblTimes.gridx = 3;
		gbc_lblTimes.gridy = 1;
		panel_1.add(lblTimes, gbc_lblTimes);
		
		ckDebug = new JCheckBox("");
		GridBagConstraints gbc_ckDebug = new GridBagConstraints();
		gbc_ckDebug.insets = new Insets(0, 0, 5, 5);
		gbc_ckDebug.gridx = 0;
		gbc_ckDebug.gridy = 2;
		panel_1.add(ckDebug, gbc_ckDebug);
		
		lblShowDebugMessages = new JLabel("show debug messages");
		GridBagConstraints gbc_lblShowDebugMessages = new GridBagConstraints();
		gbc_lblShowDebugMessages.insets = new Insets(0, 0, 5, 5);
		gbc_lblShowDebugMessages.anchor = GridBagConstraints.WEST;
		gbc_lblShowDebugMessages.gridwidth = 3;
		gbc_lblShowDebugMessages.gridx = 1;
		gbc_lblShowDebugMessages.gridy = 2;
		panel_1.add(lblShowDebugMessages, gbc_lblShowDebugMessages);
		
		ckEncoder = new JCheckBox("");
		GridBagConstraints gbc_ckEncoder = new GridBagConstraints();
		gbc_ckEncoder.insets = new Insets(0, 0, 5, 5);
		gbc_ckEncoder.gridx = 0;
		gbc_ckEncoder.gridy = 3;
		panel_1.add(ckEncoder, gbc_ckEncoder);
		
		lblUse = new JLabel("use");
		GridBagConstraints gbc_lblUse = new GridBagConstraints();
		gbc_lblUse.anchor = GridBagConstraints.WEST;
		gbc_lblUse.insets = new Insets(0, 0, 5, 5);
		gbc_lblUse.gridx = 1;
		gbc_lblUse.gridy = 3;
		panel_1.add(lblUse, gbc_lblUse);
		
		comboBox = new JComboBox<String>();
		comboBox.setModel(new DefaultComboBoxModel<String>(new String[] {"ffmpeg", "avconv"}));
		GridBagConstraints gbc_comboBox = new GridBagConstraints();
		gbc_comboBox.insets = new Insets(0, 0, 5, 5);
		gbc_comboBox.fill = GridBagConstraints.HORIZONTAL;
		gbc_comboBox.gridx = 2;
		gbc_comboBox.gridy = 3;
		panel_1.add(comboBox, gbc_comboBox);
		
		lblEncoder = new JLabel("encoder");
		GridBagConstraints gbc_lblEncoder = new GridBagConstraints();
		gbc_lblEncoder.anchor = GridBagConstraints.WEST;
		gbc_lblEncoder.insets = new Insets(0, 0, 5, 5);
		gbc_lblEncoder.gridx = 3;
		gbc_lblEncoder.gridy = 3;
		panel_1.add(lblEncoder, gbc_lblEncoder);
		
		ckKeepPNG = new JCheckBox("");
		GridBagConstraints gbc_ckKeepPNG = new GridBagConstraints();
		gbc_ckKeepPNG.insets = new Insets(0, 0, 5, 5);
		gbc_ckKeepPNG.gridx = 0;
		gbc_ckKeepPNG.gridy = 4;
		panel_1.add(ckKeepPNG, gbc_ckKeepPNG);
		
		lblKeepPngs = new JLabel("keep png's");
		GridBagConstraints gbc_lblKeepPngs = new GridBagConstraints();
		gbc_lblKeepPngs.insets = new Insets(0, 0, 5, 5);
		gbc_lblKeepPngs.anchor = GridBagConstraints.WEST;
		gbc_lblKeepPngs.gridwidth = 3;
		gbc_lblKeepPngs.gridx = 1;
		gbc_lblKeepPngs.gridy = 4;
		panel_1.add(lblKeepPngs, gbc_lblKeepPngs);
		
		ckOutputDir = new JCheckBox("");
		GridBagConstraints gbc_ckOutputDir = new GridBagConstraints();
		gbc_ckOutputDir.insets = new Insets(0, 0, 5, 5);
		gbc_ckOutputDir.gridx = 0;
		gbc_ckOutputDir.gridy = 5;
		panel_1.add(ckOutputDir, gbc_ckOutputDir);
		
		lblOutputDir = new JLabel("output dir");
		GridBagConstraints gbc_lblOutputDir = new GridBagConstraints();
		gbc_lblOutputDir.anchor = GridBagConstraints.EAST;
		gbc_lblOutputDir.insets = new Insets(0, 0, 5, 5);
		gbc_lblOutputDir.gridx = 1;
		gbc_lblOutputDir.gridy = 5;
		panel_1.add(lblOutputDir, gbc_lblOutputDir);
		
		textField_5 = new JTextField();
		GridBagConstraints gbc_textField_5 = new GridBagConstraints();
		gbc_textField_5.insets = new Insets(0, 0, 5, 5);
		gbc_textField_5.gridwidth = 3;
		gbc_textField_5.fill = GridBagConstraints.HORIZONTAL;
		gbc_textField_5.gridx = 2;
		gbc_textField_5.gridy = 5;
		panel_1.add(textField_5, gbc_textField_5);
		textField_5.setColumns(10);
		
		ckUseShortArgs = new JCheckBox("");
		GridBagConstraints gbc_ckUseShortArgs = new GridBagConstraints();
		gbc_ckUseShortArgs.insets = new Insets(0, 0, 5, 5);
		gbc_ckUseShortArgs.gridx = 0;
		gbc_ckUseShortArgs.gridy = 6;
		panel_1.add(ckUseShortArgs, gbc_ckUseShortArgs);
		
		lblNewLabel = new JLabel("use shorter arguments");
		GridBagConstraints gbc_lblNewLabel = new GridBagConstraints();
		gbc_lblNewLabel.insets = new Insets(0, 0, 5, 5);
		gbc_lblNewLabel.anchor = GridBagConstraints.WEST;
		gbc_lblNewLabel.gridwidth = 3;
		gbc_lblNewLabel.gridx = 1;
		gbc_lblNewLabel.gridy = 6;
		panel_1.add(lblNewLabel, gbc_lblNewLabel);
		
		lblLaunchCommand = new JLabel("Launch command");
		GridBagConstraints gbc_lblLaunchCommand = new GridBagConstraints();
		gbc_lblLaunchCommand.gridwidth = 3;
		gbc_lblLaunchCommand.anchor = GridBagConstraints.WEST;
		gbc_lblLaunchCommand.insets = new Insets(0, 0, 5, 5);
		gbc_lblLaunchCommand.gridx = 0;
		gbc_lblLaunchCommand.gridy = 11;
		panel_1.add(lblLaunchCommand, gbc_lblLaunchCommand);
		
		lblEstimatedMemoryUsage = new JLabel("Estimated memory usage:");
		GridBagConstraints gbc_lblEstimatedMemoryUsage = new GridBagConstraints();
		gbc_lblEstimatedMemoryUsage.anchor = GridBagConstraints.EAST;
		gbc_lblEstimatedMemoryUsage.insets = new Insets(0, 0, 5, 5);
		gbc_lblEstimatedMemoryUsage.gridx = 3;
		gbc_lblEstimatedMemoryUsage.gridy = 11;
		panel_1.add(lblEstimatedMemoryUsage, gbc_lblEstimatedMemoryUsage);
		
		textField_7 = new JTextField();
		textField_7.setHorizontalAlignment(SwingConstants.RIGHT);
		textField_7.setEditable(false);
		GridBagConstraints gbc_textField_7 = new GridBagConstraints();
		gbc_textField_7.insets = new Insets(0, 0, 5, 0);
		gbc_textField_7.fill = GridBagConstraints.HORIZONTAL;
		gbc_textField_7.gridx = 4;
		gbc_textField_7.gridy = 11;
		panel_1.add(textField_7, gbc_textField_7);
		textField_7.setColumns(10);
		
		textPane_4 = new JTextPane();
		textPane_4.setEditable(false);
		GridBagConstraints gbc_textPane_4 = new GridBagConstraints();
		gbc_textPane_4.insets = new Insets(0, 0, 0, 5);
		gbc_textPane_4.gridheight = 3;
		gbc_textPane_4.gridwidth = 5;
		gbc_textPane_4.fill = GridBagConstraints.BOTH;
		gbc_textPane_4.gridx = 0;
		gbc_textPane_4.gridy = 12;
		panel_1.add(textPane_4, gbc_textPane_4);
		
		panel_2 = new JPanel();
		tabbedPane.addTab("Creation", null, panel_2, null);
		GridBagLayout gbl_panel_2 = new GridBagLayout();
		gbl_panel_2.columnWidths = new int[]{395, 0};
		gbl_panel_2.rowHeights = new int[]{21, 0, 0, 0};
		gbl_panel_2.columnWeights = new double[]{1.0, Double.MIN_VALUE};
		gbl_panel_2.rowWeights = new double[]{1.0, 0.0, 0.0, Double.MIN_VALUE};
		panel_2.setLayout(gbl_panel_2);
		
		textPane = new JTextPane();
		GridBagConstraints gbc_textPane = new GridBagConstraints();
		gbc_textPane.insets = new Insets(0, 0, 5, 0);
		gbc_textPane.fill = GridBagConstraints.BOTH;
		gbc_textPane.gridx = 0;
		gbc_textPane.gridy = 0;
		panel_2.add(textPane, gbc_textPane);
		
		lblTTimeFrame = new JLabel("<html><font color='red'>t</font>: time frame (0 to duration-1),\n<font color='red'>s</font>: total duration,\n<font color='red'>d</font>: dimensions of the system (1->1D, 2-> 2D, etc.)</html>");
		GridBagConstraints gbc_lblTTimeFrame = new GridBagConstraints();
		gbc_lblTTimeFrame.anchor = GridBagConstraints.WEST;
		gbc_lblTTimeFrame.insets = new Insets(0, 0, 5, 0);
		gbc_lblTTimeFrame.gridx = 0;
		gbc_lblTTimeFrame.gridy = 1;
		panel_2.add(lblTTimeFrame, gbc_lblTTimeFrame);
		
		label = new JLabel("");
		GridBagConstraints gbc_label = new GridBagConstraints();
		gbc_label.gridx = 0;
		gbc_label.gridy = 2;
		panel_2.add(label, gbc_label);
		
		panel_3 = new JPanel();
		tabbedPane.addTab("Grow", null, panel_3, null);
		GridBagLayout gbl_panel_3 = new GridBagLayout();
		gbl_panel_3.columnWidths = new int[]{0, 0};
		gbl_panel_3.rowHeights = new int[]{0, 0, 0};
		gbl_panel_3.columnWeights = new double[]{1.0, Double.MIN_VALUE};
		gbl_panel_3.rowWeights = new double[]{1.0, 0.0, Double.MIN_VALUE};
		panel_3.setLayout(gbl_panel_3);
		
		textPane_1 = new JTextPane();
		GridBagConstraints gbc_textPane_1 = new GridBagConstraints();
		gbc_textPane_1.insets = new Insets(0, 0, 5, 0);
		gbc_textPane_1.fill = GridBagConstraints.BOTH;
		gbc_textPane_1.gridx = 0;
		gbc_textPane_1.gridy = 0;
		panel_3.add(textPane_1, gbc_textPane_1);
		
		lblNewLabel_1 = new JLabel("<html><font color=\"red\">i</font>: current cluster id, <font color=\"red\">t</font>: current time frame, <font color=\"red\">s</font>: duration, <font color=\"red\">r</font>: current cluster radius, <font color=\"red\">v</font>: current cluster volume, <font color=\"red\">c</font>: cluster creation time frame (0,1,...), <font color=\"red\">d</font>: dimensions of the system (1 => 1D, 2 => 2D, etc.)\n</html>");
		GridBagConstraints gbc_lblNewLabel_1 = new GridBagConstraints();
		gbc_lblNewLabel_1.fill = GridBagConstraints.HORIZONTAL;
		gbc_lblNewLabel_1.gridx = 0;
		gbc_lblNewLabel_1.gridy = 1;
		panel_3.add(lblNewLabel_1, gbc_lblNewLabel_1);
		
		panel_4 = new JPanel();
		tabbedPane.addTab("Position", null, panel_4, null);
		GridBagLayout gbl_panel_4 = new GridBagLayout();
		gbl_panel_4.columnWidths = new int[]{0, 100, 0};
		gbl_panel_4.rowHeights = new int[]{0, 0, 0, 0};
		gbl_panel_4.columnWeights = new double[]{1.0, 0.0, Double.MIN_VALUE};
		gbl_panel_4.rowWeights = new double[]{0.0, 1.0, 0.0, Double.MIN_VALUE};
		panel_4.setLayout(gbl_panel_4);
		
		ckGeneralPosition = new JCheckBox("Use just a formula for all axes");
		ckGeneralPosition.addItemListener(new ItemListener() {
			public void itemStateChanged(ItemEvent e) {
				updatePositionAxisModel();
			}
		});
		ckGeneralPosition.addChangeListener(new ChangeListener() {
			public void stateChanged(ChangeEvent e) {
				
			}
		});
		GridBagConstraints gbc_ckGeneralPosition = new GridBagConstraints();
		gbc_ckGeneralPosition.anchor = GridBagConstraints.WEST;
		gbc_ckGeneralPosition.insets = new Insets(0, 0, 5, 5);
		gbc_ckGeneralPosition.gridx = 0;
		gbc_ckGeneralPosition.gridy = 0;
		panel_4.add(ckGeneralPosition, gbc_ckGeneralPosition);
		
		comboBoxPositionAxis = new JComboBox();
		comboBoxPositionAxis.addItemListener(new ItemListener() {
			public void itemStateChanged(ItemEvent e) {
				MainForm.this.setCurrentSelectedPositionFunc(comboBoxPositionAxis.getSelectedIndex());
				loadClusterPosition();
			}
		});
		GridBagConstraints gbc_comboBox_1 = new GridBagConstraints();
		gbc_comboBox_1.insets = new Insets(0, 0, 5, 0);
		gbc_comboBox_1.fill = GridBagConstraints.HORIZONTAL;
		gbc_comboBox_1.gridx = 1;
		gbc_comboBox_1.gridy = 0;
		panel_4.add(comboBoxPositionAxis, gbc_comboBox_1);
		
		textPane_3 = new JTextPane();
		textPane_3.addFocusListener(new FocusAdapter() {
			@Override
			public void focusGained(FocusEvent e) {
				loadClusterPosition();
			}
			
			@Override
			public void focusLost(FocusEvent e) {
				saveClusterPosition();
			}
		});
		GridBagConstraints gbc_textPane_3 = new GridBagConstraints();
		gbc_textPane_3.insets = new Insets(0, 0, 5, 0);
		gbc_textPane_3.gridwidth = 2;
		gbc_textPane_3.fill = GridBagConstraints.BOTH;
		gbc_textPane_3.gridx = 0;
		gbc_textPane_3.gridy = 1;
		panel_4.add(textPane_3, gbc_textPane_3);
		
		lblNewLabel_2 = new JLabel("<html>\n<font color=\"red\">i</font>: current cluster id,\n<font color=\"red\">j</font>: counter that indicate the inserting order (start from 0 and is resetted at every timeframe),\n<font color=\"red\">t</font>: current time frame,\n<font color=\"red\">s</font>: total duration,\n<font color=\"red\">w</font>: container size in the current dimension,\n<font color=\"red\">d</font>: dimensions of the system (1 => 1D, 2 => 2D, etc.)\n</html>");
		GridBagConstraints gbc_lblNewLabel_2 = new GridBagConstraints();
		gbc_lblNewLabel_2.fill = GridBagConstraints.HORIZONTAL;
		gbc_lblNewLabel_2.gridwidth = 2;
		gbc_lblNewLabel_2.insets = new Insets(0, 0, 0, 5);
		gbc_lblNewLabel_2.gridx = 0;
		gbc_lblNewLabel_2.gridy = 2;
		panel_4.add(lblNewLabel_2, gbc_lblNewLabel_2);
		
		panel_5 = new JPanel();
		tabbedPane.addTab("Common", null, panel_5, null);
		GridBagLayout gbl_panel_5 = new GridBagLayout();
		gbl_panel_5.columnWidths = new int[]{0, 0};
		gbl_panel_5.rowHeights = new int[]{0, 0};
		gbl_panel_5.columnWeights = new double[]{1.0, Double.MIN_VALUE};
		gbl_panel_5.rowWeights = new double[]{1.0, Double.MIN_VALUE};
		panel_5.setLayout(gbl_panel_5);
		
		textPane_2 = new JTextPane();
		GridBagConstraints gbc_textPane_2 = new GridBagConstraints();
		gbc_textPane_2.fill = GridBagConstraints.BOTH;
		gbc_textPane_2.gridx = 0;
		gbc_textPane_2.gridy = 0;
		panel_5.add(textPane_2, gbc_textPane_2);
		
		panel_7 = new JPanel();
		tabbedPane.addTab("Render", null, panel_7, null);
		GridBagLayout gbl_panel_7 = new GridBagLayout();
		gbl_panel_7.columnWidths = new int[]{0, 0, 0, 0};
		gbl_panel_7.rowHeights = new int[]{0, 0, 0};
		gbl_panel_7.columnWeights = new double[]{1.0, 0.0, 0.0, Double.MIN_VALUE};
		gbl_panel_7.rowWeights = new double[]{0.0, 1.0, Double.MIN_VALUE};
		panel_7.setLayout(gbl_panel_7);
		
		btnAdd = new JButton("Add");
		GridBagConstraints gbc_btnAdd = new GridBagConstraints();
		gbc_btnAdd.insets = new Insets(0, 0, 5, 5);
		gbc_btnAdd.gridx = 1;
		gbc_btnAdd.gridy = 0;
		panel_7.add(btnAdd, gbc_btnAdd);
		
		btnDelButton = new JButton("Del");
		GridBagConstraints gbc_btnDelButton = new GridBagConstraints();
		gbc_btnDelButton.anchor = GridBagConstraints.EAST;
		gbc_btnDelButton.insets = new Insets(0, 0, 5, 0);
		gbc_btnDelButton.gridx = 2;
		gbc_btnDelButton.gridy = 0;
		panel_7.add(btnDelButton, gbc_btnDelButton);
		
		textPane_5 = new JTextPane();
		GridBagConstraints gbc_textPane_5 = new GridBagConstraints();
		gbc_textPane_5.gridheight = 2;
		gbc_textPane_5.insets = new Insets(0, 0, 0, 5);
		gbc_textPane_5.fill = GridBagConstraints.BOTH;
		gbc_textPane_5.gridx = 0;
		gbc_textPane_5.gridy = 0;
		panel_7.add(textPane_5, gbc_textPane_5);
		
		list_1 = new JList();
		GridBagConstraints gbc_list_1 = new GridBagConstraints();
		gbc_list_1.gridwidth = 2;
		gbc_list_1.fill = GridBagConstraints.BOTH;
		gbc_list_1.gridx = 1;
		gbc_list_1.gridy = 1;
		panel_7.add(list_1, gbc_list_1);
		
		
		
		addWindowListener(new WindowAdapter() {
			@Override
			public void windowClosing(WindowEvent e) {
				int response = JOptionPane.showConfirmDialog(MainForm.this, String.format("Do you want to save the modification on file '%s'?", file.getName()), "Save?", JOptionPane.YES_NO_CANCEL_OPTION);
				
				switch (response)
				{
					case JOptionPane.CANCEL_OPTION:
					break;
					
					case JOptionPane.YES_OPTION:
					try {
						saveConfig(simulation, file);
					} catch (ParseException | IOException e1) {
						throw new RuntimeException(e1);
					}
						MainForm.this.dispose();
					break;
					
					case JOptionPane.NO_OPTION:
						MainForm.this.dispose();
					break;
				}
			}
		});
		
		updatePositionAxisModel();
		
		initDataBindings();
		
		setVisible(true);
	}

	@SuppressWarnings("unchecked")
	private void updatePositionAxisModel() {
		if (comboBoxPositionAxis.getModel().getSize() > 0)
			comboBoxPositionAxis.setSelectedIndex(0);
		
		DefaultComboBoxModel<Object> comboBoxPositionAxisModel = new DefaultComboBoxModel<>();
		for (String label: getPositionFuncsLabels())
			comboBoxPositionAxisModel.addElement(label);
		comboBoxPositionAxis.setModel(comboBoxPositionAxisModel);
	}
	
	public int getCurrentSelectedPositionFunc() {
		return currentSelectedPositionFunc;
	}
	
	public void setCurrentSelectedPositionFunc(int currentSelectedPositionFunc) {
		this.currentSelectedPositionFunc = currentSelectedPositionFunc;
	}
	
	public static SimulationConfig loadConfig(File file) throws FileNotFoundException, ParseException
	{
		if (file == null)
		{
			JOptionPane.showMessageDialog(null, "No file was provided", "Error", JOptionPane.ERROR_MESSAGE);
			return null;
		}
		
		if (!file.exists())
		{
			JOptionPane.showMessageDialog(null, String.format("Unable to read file: %s", file.toString()), "Error", JOptionPane.ERROR_MESSAGE);
			return null;
		}
		
		
		StringBuffer buffer = new StringBuffer();
		// Reading the entire file
		try(Scanner scanner = new Scanner(file))
		{
		boolean hasComment = false;
		
		while (scanner.hasNextLine())
		{
			String line = scanner.nextLine();
			
			if (line.trim().startsWith("#") || line.trim().startsWith(";"))
				hasComment = true;
			else
				buffer.append(line + "\n");
			
		}
		
		boolean wantToContinue = true;
		
		if (hasComment)
			wantToContinue = JOptionPane.showOptionDialog(null, "In the configuration file was found some comments. Using this tool you may lose these comments. Are you sure you want to continue?", "Warning", JOptionPane.YES_NO_OPTION,
				    JOptionPane.WARNING_MESSAGE, null, null, JOptionPane.NO_OPTION) == JOptionPane.YES_OPTION;
		
	
		
		if (!wantToContinue)
			return null;
		
		
		SimulationConfig sim = new SimulationConfig();
		
		ConfigParser parser = new ConfigParser(new StringReader(buffer.toString()));
		Config conf = parser.buildConfiguration();
		
		Setting confSimulation = conf.lookup("simulation");
		
		//sim.setContainerSize(conf.getA);
		sim.setBasename((String) confSimulation.lookupValue("basename"));
		sim.setDimensions((String) confSimulation.lookupValue("dimensions"));
		sim.setDuration((Integer) confSimulation.lookupValue("duration"));
		
		ArrayList<Integer> containerSize = new ArrayList<>();
		for (Setting size: (Setting[]) confSimulation.lookupValue("container_size"))
			containerSize.add((Integer) size.getValue());
		sim.setContainerSize(containerSize);
		
		
		sim.setStopWhenVolumeIs((Double) confSimulation.lookupValue("stop_when_volume_is"));
		
		sim.setPeriodicBoundaries((Boolean) confSimulation.lookupValue("periodic_boundaries"));
		sim.setUnconstrainedGrow((Boolean) confSimulation.lookupValue("unconstrained_grow"));

		sim.setAvramiFitMinVolume((Double) confSimulation.lookupValue("avrami_fit_min_volume"));
		sim.setAvramiFitMaxVolume((Double) confSimulation.lookupValue("avrami_fit_max_volume"));

		sim.setClusterCreationFunc((String) confSimulation.lookupValue("cluster_creation_func"));
		sim.setClusterGrowFunc((String) confSimulation.lookupValue("cluster_grow_func"));
		
		
		
		
		// Set position functions
		ArrayList<String> clusterPositionFuncs = new ArrayList<String>();
		
		if (confSimulation.isSettingExists("cluster_position_func"))
		{
			sim.setGenericPosition(true);
			clusterPositionFuncs.add((String) confSimulation.lookupValue("cluster_position_func"));
		}
		else
		{
			sim.setGenericPosition(true);
			if (confSimulation.isSettingExists("cluster_position_func_x"))
				clusterPositionFuncs.add((String) confSimulation.lookupValue("cluster_position_func_x"));
			if (confSimulation.isSettingExists("cluster_position_func_y"))
				clusterPositionFuncs.add((String) confSimulation.lookupValue("cluster_position_func_y"));
			if (confSimulation.isSettingExists("cluster_position_func_z"))
				clusterPositionFuncs.add((String) confSimulation.lookupValue("cluster_position_func_z"));
			
			int j = 1;
			while (true)
			{
				 String value = confSimulation.lookupValue(String.format("cluster_position_func_r%d", j++));
				 if (value != null)
					 clusterPositionFuncs.add(value);
				 else
					 break;
			}
		}
		
		sim.setClusterPositionFuncs(clusterPositionFuncs);
		
		//
		
		// Setting common functions
		ArrayList<String> commonFuncs = new ArrayList<String>();
		
		int i = 1;
		while (true)
		{
			 String value = confSimulation.lookupValue(String.format("common_func_%d", i++));
			 if (value != null)
				 commonFuncs.add(value);
			 else
				 break;
		}
		sim.setCommonFuncs(commonFuncs);
		//
		
	
		
		return sim;
		}
		
		
	}
	
	@SuppressWarnings("unchecked")
	public static void saveConfig(SimulationConfig sim, File file) throws ParseException, IOException
	{
	
		Config conf = new Config();
		
		
		Setting confSimulation = conf.lookup("simulation");
		
		if (confSimulation == null)
			confSimulation = conf.addGroup("simulation");
		
		
		//sim.setContainerSize(conf.getA);

		confSimulation.addScalar("basename", sim.getBasename());
		confSimulation.addScalar("dimensions", sim.getDimensions());
		confSimulation.addScalar("duration", sim.getDuration());
		confSimulation.addScalar("stop_when_volume_is", sim.getStopWhenVolumeIs());
		
		confSimulation.addScalar("periodic_boundaries", sim.isPeriodicBoundaries());
		confSimulation.addScalar("unconstrained_grow", sim.isUnconstrainedGrow());
		confSimulation.addScalar("avrami_fit_min_volume", sim.getAvramiFitMinVolume());
		confSimulation.addScalar("avrami_fit_max_volume", sim.getAvramiFitMaxVolume());
		
		confSimulation.addScalar("cluster_creation_func", sim.getClusterCreationFunc());
		confSimulation.addScalar("cluster_grow_func", sim.getClusterGrowFunc());
		
		confSimulation.addArray("container_size", sim.getContainerSize().toArray());
		
		
		// Set position functions
		
		
		// clearing existing funcs
		ArrayList<String> toRemovePos = new ArrayList<String>();
		for (Setting element: ((List<Setting>) confSimulation.getValue()))
		{
			if (element.getName().startsWith("cluster_position_func"))
				toRemovePos.add(element.getName());
		}
		
		for (String name: toRemovePos)
			confSimulation.removeScalar(name);
		//
		
		if (sim.isGenericPosition())
		{
			
			if (sim.getClusterPositionFuncs() != null && !sim.getClusterPositionFuncs().isEmpty())
				confSimulation.addScalar("cluster_position_func", sim.getClusterPositionFuncs().get(0));
		}
		else
		{
			if (sim.getClusterPositionFuncs() != null && sim.getClusterPositionFuncs().size() <= 3)
			{
				if (sim.getClusterPositionFuncs().size() >= 1)
					confSimulation.addScalar("cluster_position_func_x", sim.getClusterPositionFuncs().get(0));
				if (sim.getClusterPositionFuncs().size() >= 2)
					confSimulation.addScalar("cluster_position_func_y", sim.getClusterPositionFuncs().get(1));
				if (sim.getClusterPositionFuncs().size() >= 3)
					confSimulation.addScalar("cluster_position_func_z", sim.getClusterPositionFuncs().get(2));
			}
			else
			{
				for (int i = 0; i < sim.getClusterPositionFuncs().size(); i++)
				{
					confSimulation.addScalar(String.format("cluster_position_func_r%d", i+1), sim.getClusterPositionFuncs().get(i));
				}
			}			
			
		}
		//
		
		// Setting common functions
		// clearing existing funcs
		ArrayList<String> toRemoveComm = new ArrayList<String>();
		for (Setting element: ((List<Setting>) confSimulation.getValue()))
		{
			if (element.getName().startsWith("common_func_"))
				toRemoveComm.add(element.getName());
		}
		
		for (String name: toRemoveComm)
			confSimulation.removeScalar(name);
		//
		
		
		for (int i = 0; i < sim.getCommonFuncs().size(); i++)
		{
			confSimulation.addScalar(String.format("common_func_%d", i+1), sim.getCommonFuncs().get(i));
		}
		
		
		new ConfigOutputter().output(conf, file);
		
	}
	
	public static class PercentualConverter extends Converter<Double, String>
	{

		@Override
		public String convertForward(Double arg0) {
			return String.format("%.2f%%", arg0 * 100);
		}

		@Override
		public Double convertReverse(String arg0) {
			String s = StringUtils.trimToNull(StringUtils.replace(arg0, "%", ""));
			
			if (s != null)
				return Double.parseDouble(s) / 100;
			else
				return null;
		}
		
	}
	
	public static class PercentualValidator extends Validator<Double>
	{

		@Override
		public Validator<Double>.Result validate(Double arg0) {
		
			if ((arg0 < 0.0) || (arg0 > 1.0))
				return new Result(null, "Value must be between 0% and 100%");
		    
			return null;
		}
		
	}
	
	public static class BiggerThanZeroValidator extends Validator<Integer>
	{

		@Override
		public Validator<Integer>.Result validate(Integer arg0) {
			if (arg0 <= 0)
				return new Result(null, "Value must be al least 1");
			return null;
		}
		
	}
	
	
	private JLabel lblEstimatedMemoryUsage;
	private JTextField textField_7;
	private JTextField textField_8;
	private JPanel panel_7;
	private JComboBox comboBoxPositionAxis;
	private JTextPane textPane_5;
	private JList list_1;
	private JButton btnDelButton;
	private JButton btnAdd;
	private JLabel label;
	private JLabel lblTTimeFrame;
	private JLabel lblNewLabel_1;
	private JLabel lblNewLabel_2;

	private void loadClusterPosition() {
		textPane_3.setText(simulation.getClusterPositionFuncs().get(currentSelectedPositionFunc));
	}

	private void saveClusterPosition() {
		simulation.getClusterPositionFuncs().set(currentSelectedPositionFunc, textPane_3.getText());
	}
	protected void initDataBindings() {
		BeanProperty<CmdLineLauncher, Boolean> cmdLineLauncherBeanProperty = BeanProperty.create("enThreads");
		BeanProperty<JCheckBox, Boolean> jCheckBoxBeanProperty = BeanProperty.create("selected");
		AutoBinding<CmdLineLauncher, Boolean, JCheckBox, Boolean> autoBinding = Bindings.createAutoBinding(UpdateStrategy.READ_WRITE, cmdLineLauncher, cmdLineLauncherBeanProperty, ckThreads, jCheckBoxBeanProperty);
		autoBinding.bind();
		//
		BeanProperty<CmdLineLauncher, Boolean> cmdLineLauncherBeanProperty_1 = BeanProperty.create("enRepeat");
		AutoBinding<CmdLineLauncher, Boolean, JCheckBox, Boolean> autoBinding_1 = Bindings.createAutoBinding(UpdateStrategy.READ_WRITE, cmdLineLauncher, cmdLineLauncherBeanProperty_1, ckRepeat, jCheckBoxBeanProperty);
		autoBinding_1.bind();
		//
		BeanProperty<CmdLineLauncher, Boolean> cmdLineLauncherBeanProperty_2 = BeanProperty.create("enDebug");
		AutoBinding<CmdLineLauncher, Boolean, JCheckBox, Boolean> autoBinding_2 = Bindings.createAutoBinding(UpdateStrategy.READ_WRITE, cmdLineLauncher, cmdLineLauncherBeanProperty_2, ckDebug, jCheckBoxBeanProperty);
		autoBinding_2.bind();
		//
		BeanProperty<CmdLineLauncher, Boolean> cmdLineLauncherBeanProperty_3 = BeanProperty.create("enEncoder");
		AutoBinding<CmdLineLauncher, Boolean, JCheckBox, Boolean> autoBinding_3 = Bindings.createAutoBinding(UpdateStrategy.READ_WRITE, cmdLineLauncher, cmdLineLauncherBeanProperty_3, ckEncoder, jCheckBoxBeanProperty);
		autoBinding_3.bind();
		//
		BeanProperty<CmdLineLauncher, Boolean> cmdLineLauncherBeanProperty_4 = BeanProperty.create("enKeepPNG");
		AutoBinding<CmdLineLauncher, Boolean, JCheckBox, Boolean> autoBinding_4 = Bindings.createAutoBinding(UpdateStrategy.READ_WRITE, cmdLineLauncher, cmdLineLauncherBeanProperty_4, ckKeepPNG, jCheckBoxBeanProperty);
		autoBinding_4.bind();
		//
		BeanProperty<CmdLineLauncher, Boolean> cmdLineLauncherBeanProperty_5 = BeanProperty.create("enOutputDir");
		AutoBinding<CmdLineLauncher, Boolean, JCheckBox, Boolean> autoBinding_5 = Bindings.createAutoBinding(UpdateStrategy.READ_WRITE, cmdLineLauncher, cmdLineLauncherBeanProperty_5, ckOutputDir, jCheckBoxBeanProperty);
		autoBinding_5.bind();
		//
		BeanProperty<CmdLineLauncher, Boolean> cmdLineLauncherBeanProperty_6 = BeanProperty.create("enShortArgs");
		AutoBinding<CmdLineLauncher, Boolean, JCheckBox, Boolean> autoBinding_6 = Bindings.createAutoBinding(UpdateStrategy.READ_WRITE, cmdLineLauncher, cmdLineLauncherBeanProperty_6, ckUseShortArgs, jCheckBoxBeanProperty);
		autoBinding_6.bind();
		//
		BeanProperty<CmdLineLauncher, String> cmdLineLauncherBeanProperty_7 = BeanProperty.create("commandLine");
		BeanProperty<JTextPane, String> jTextPaneBeanProperty = BeanProperty.create("text");
		AutoBinding<CmdLineLauncher, String, JTextPane, String> autoBinding_7 = Bindings.createAutoBinding(UpdateStrategy.READ, cmdLineLauncher, cmdLineLauncherBeanProperty_7, textPane_4, jTextPaneBeanProperty);
		autoBinding_7.bind();
		//
		BeanProperty<CmdLineLauncher, String> cmdLineLauncherBeanProperty_10 = BeanProperty.create("encoder");
		BeanProperty<JComboBox, Object> jComboBoxBeanProperty = BeanProperty.create("selectedItem");
		AutoBinding<CmdLineLauncher, String, JComboBox, Object> autoBinding_10 = Bindings.createAutoBinding(UpdateStrategy.READ_WRITE, cmdLineLauncher, cmdLineLauncherBeanProperty_10, comboBox, jComboBoxBeanProperty);
		autoBinding_10.bind();
		//
		BeanProperty<CmdLineLauncher, String> cmdLineLauncherBeanProperty_11 = BeanProperty.create("outpudDir");
		BeanProperty<JTextField, String> jTextFieldBeanProperty_2 = BeanProperty.create("text");
		AutoBinding<CmdLineLauncher, String, JTextField, String> autoBinding_11 = Bindings.createAutoBinding(UpdateStrategy.READ_WRITE, cmdLineLauncher, cmdLineLauncherBeanProperty_11, textField_5, jTextFieldBeanProperty_2);
		autoBinding_11.bind();
		//
		BeanProperty<JLabel, Boolean> jLabelBeanProperty = BeanProperty.create("enabled");
		AutoBinding<JCheckBox, Boolean, JLabel, Boolean> autoBinding_12 = Bindings.createAutoBinding(UpdateStrategy.READ, ckThreads, jCheckBoxBeanProperty, lblUseUpTo, jLabelBeanProperty);
		autoBinding_12.bind();
		//
		AutoBinding<JCheckBox, Boolean, JLabel, Boolean> autoBinding_14 = Bindings.createAutoBinding(UpdateStrategy.READ, ckThreads, jCheckBoxBeanProperty, lblThreads, jLabelBeanProperty);
		autoBinding_14.bind();
		//
		AutoBinding<JCheckBox, Boolean, JLabel, Boolean> autoBinding_15 = Bindings.createAutoBinding(UpdateStrategy.READ, ckRepeat, jCheckBoxBeanProperty, lblRepeat, jLabelBeanProperty);
		autoBinding_15.bind();
		//
		AutoBinding<JCheckBox, Boolean, JLabel, Boolean> autoBinding_17 = Bindings.createAutoBinding(UpdateStrategy.READ, ckRepeat, jCheckBoxBeanProperty, lblTimes, jLabelBeanProperty);
		autoBinding_17.bind();
		//
		AutoBinding<JCheckBox, Boolean, JLabel, Boolean> autoBinding_18 = Bindings.createAutoBinding(UpdateStrategy.READ, ckDebug, jCheckBoxBeanProperty, lblShowDebugMessages, jLabelBeanProperty);
		autoBinding_18.bind();
		//
		AutoBinding<JCheckBox, Boolean, JLabel, Boolean> autoBinding_19 = Bindings.createAutoBinding(UpdateStrategy.READ, ckEncoder, jCheckBoxBeanProperty, lblUse, jLabelBeanProperty);
		autoBinding_19.bind();
		//
		BeanProperty<JComboBox, Boolean> jComboBoxBeanProperty_1 = BeanProperty.create("enabled");
		AutoBinding<JCheckBox, Boolean, JComboBox, Boolean> autoBinding_20 = Bindings.createAutoBinding(UpdateStrategy.READ, ckEncoder, jCheckBoxBeanProperty, comboBox, jComboBoxBeanProperty_1);
		autoBinding_20.bind();
		//
		AutoBinding<JCheckBox, Boolean, JLabel, Boolean> autoBinding_21 = Bindings.createAutoBinding(UpdateStrategy.READ, ckEncoder, jCheckBoxBeanProperty, lblEncoder, jLabelBeanProperty);
		autoBinding_21.bind();
		//
		AutoBinding<JCheckBox, Boolean, JLabel, Boolean> autoBinding_22 = Bindings.createAutoBinding(UpdateStrategy.READ, ckKeepPNG, jCheckBoxBeanProperty, lblKeepPngs, jLabelBeanProperty);
		autoBinding_22.bind();
		//
		AutoBinding<JCheckBox, Boolean, JLabel, Boolean> autoBinding_23 = Bindings.createAutoBinding(UpdateStrategy.READ, ckOutputDir, jCheckBoxBeanProperty, lblOutputDir, jLabelBeanProperty);
		autoBinding_23.bind();
		//
		BeanProperty<JTextField, Boolean> jTextFieldBeanProperty_3 = BeanProperty.create("enabled");
		AutoBinding<JCheckBox, Boolean, JTextField, Boolean> autoBinding_24 = Bindings.createAutoBinding(UpdateStrategy.READ, ckOutputDir, jCheckBoxBeanProperty, textField_5, jTextFieldBeanProperty_3);
		autoBinding_24.bind();
		//
		AutoBinding<JCheckBox, Boolean, JLabel, Boolean> autoBinding_25 = Bindings.createAutoBinding(UpdateStrategy.READ, ckUseShortArgs, jCheckBoxBeanProperty, lblNewLabel, jLabelBeanProperty);
		autoBinding_25.bind();
		//
		BeanProperty<SimulationConfig, Integer> clustersimConfigBeanProperty = BeanProperty.create("duration");
		BeanProperty<JTextField, String> jTextFieldBeanProperty_4 = BeanProperty.create("text");
		AutoBinding<SimulationConfig, Integer, JTextField, String> autoBinding_26 = Bindings.createAutoBinding(UpdateStrategy.READ_WRITE, simulation, clustersimConfigBeanProperty, fieldDuration, jTextFieldBeanProperty_4);
		autoBinding_26.bind();
		//
		BeanProperty<SimulationConfig, String> clustersimConfigBeanProperty_1 = BeanProperty.create("basename");
		BeanProperty<JTextField, String> jTextFieldBeanProperty_5 = BeanProperty.create("text");
		AutoBinding<SimulationConfig, String, JTextField, String> autoBinding_27 = Bindings.createAutoBinding(UpdateStrategy.READ_WRITE, simulation, clustersimConfigBeanProperty_1, fieldBasename, jTextFieldBeanProperty_5);
		autoBinding_27.bind();
		//
		BeanProperty<SimulationConfig, String> clustersimConfigBeanProperty_2 = BeanProperty.create("dimensions");
		AutoBinding<SimulationConfig, String, JComboBox, Object> autoBinding_28 = Bindings.createAutoBinding(UpdateStrategy.READ_WRITE, simulation, clustersimConfigBeanProperty_2, comboDimensionality, jComboBoxBeanProperty);
		autoBinding_28.bind();
		//
		BeanProperty<SimulationConfig, Double> simulationConfigBeanProperty = BeanProperty.create("stopWhenVolumeIs");
		BeanProperty<JTextField, String> jTextFieldBeanProperty_6 = BeanProperty.create("text");
		AutoBinding<SimulationConfig, Double, JTextField, String> autoBinding_29 = Bindings.createAutoBinding(UpdateStrategy.READ_WRITE, simulation, simulationConfigBeanProperty, textField, jTextFieldBeanProperty_6);
		autoBinding_29.setConverter(new PercentualConverter());
		autoBinding_29.setValidator(new PercentualValidator());
		autoBinding_29.bind();
		//
		BeanProperty<SimulationConfig, Double> simulationConfigBeanProperty_1 = BeanProperty.create("avramiFitMinVolume");
		BeanProperty<JTextField, String> jTextFieldBeanProperty_7 = BeanProperty.create("text");
		AutoBinding<SimulationConfig, Double, JTextField, String> autoBinding_30 = Bindings.createAutoBinding(UpdateStrategy.READ_WRITE, simulation, simulationConfigBeanProperty_1, textField_2, jTextFieldBeanProperty_7);
		autoBinding_30.setConverter(new PercentualConverter());
		autoBinding_30.setValidator(new PercentualValidator());
		autoBinding_30.bind();
		//
		BeanProperty<SimulationConfig, Double> simulationConfigBeanProperty_2 = BeanProperty.create("avramiFitMaxVolume");
		BeanProperty<JTextField, String> jTextFieldBeanProperty_8 = BeanProperty.create("text");
		AutoBinding<SimulationConfig, Double, JTextField, String> autoBinding_31 = Bindings.createAutoBinding(UpdateStrategy.READ_WRITE, simulation, simulationConfigBeanProperty_2, textField_3, jTextFieldBeanProperty_8);
		autoBinding_31.setConverter(new PercentualConverter());
		autoBinding_31.setValidator(new PercentualValidator());
		autoBinding_31.bind();
		//
		BeanProperty<SimulationConfig, String> simulationConfigBeanProperty_3 = BeanProperty.create("clusterCreationFunc");
		BeanProperty<JTextPane, String> jTextPaneBeanProperty_1 = BeanProperty.create("text");
		AutoBinding<SimulationConfig, String, JTextPane, String> autoBinding_32 = Bindings.createAutoBinding(UpdateStrategy.READ_WRITE, simulation, simulationConfigBeanProperty_3, textPane, jTextPaneBeanProperty_1);
		autoBinding_32.bind();
		//
		BeanProperty<SimulationConfig, String> simulationConfigBeanProperty_4 = BeanProperty.create("clusterGrowFunc");
		BeanProperty<JTextPane, String> jTextPaneBeanProperty_2 = BeanProperty.create("text");
		AutoBinding<SimulationConfig, String, JTextPane, String> autoBinding_33 = Bindings.createAutoBinding(UpdateStrategy.READ_WRITE, simulation, simulationConfigBeanProperty_4, textPane_1, jTextPaneBeanProperty_2);
		autoBinding_33.bind();
		//
		BeanProperty<SimulationConfig, Boolean> simulationConfigBeanProperty_5 = BeanProperty.create("genericPosition");
		AutoBinding<SimulationConfig, Boolean, JCheckBox, Boolean> autoBinding_34 = Bindings.createAutoBinding(UpdateStrategy.READ_WRITE, simulation, simulationConfigBeanProperty_5, ckGeneralPosition, jCheckBoxBeanProperty);
		autoBinding_34.bind();
		//
		BeanProperty<File, String> fileBeanProperty = BeanProperty.create("absolutePath");
		BeanProperty<JTextField, String> jTextFieldBeanProperty_10 = BeanProperty.create("text");
		AutoBinding<File, String, JTextField, String> autoBinding_36 = Bindings.createAutoBinding(UpdateStrategy.READ, file, fileBeanProperty, textField_6, jTextFieldBeanProperty_10);
		autoBinding_36.bind();
		//
		BeanProperty<SimulationConfig, String> jPanelBeanProperty = BeanProperty.create("estimatedMemoryUsage");
		BeanProperty<JTextField, String> jTextFieldBeanProperty_9 = BeanProperty.create("text");
		AutoBinding<SimulationConfig, String, JTextField, String> autoBinding_35 = Bindings.createAutoBinding(UpdateStrategy.READ, simulation, jPanelBeanProperty, textField_7, jTextFieldBeanProperty_9);
		autoBinding_35.bind();
		//
		BeanProperty<SimulationConfig, String> simulationConfigBeanProperty_6 = BeanProperty.create("containerSizeStr");
		BeanProperty<JTextField, String> jTextFieldBeanProperty_11 = BeanProperty.create("text");
		AutoBinding<SimulationConfig, String, JTextField, String> autoBinding_37 = Bindings.createAutoBinding(UpdateStrategy.READ_WRITE, simulation, simulationConfigBeanProperty_6, textField_8, jTextFieldBeanProperty_11);
		//autoBinding_37.setConverter(new ConstainerSizeConverter());
		autoBinding_37.bind();
		//
		BeanProperty<CmdLineLauncher, Integer> cmdLineLauncherBeanProperty_8 = BeanProperty.create("threads");
		BeanProperty<JSpinner, Object> jSpinnerBeanProperty = BeanProperty.create("value");
		AutoBinding<CmdLineLauncher, Integer, JSpinner, Object> autoBinding_8 = Bindings.createAutoBinding(UpdateStrategy.READ_WRITE, cmdLineLauncher, cmdLineLauncherBeanProperty_8, textField_1, jSpinnerBeanProperty);
		autoBinding_8.setValidator(new BiggerThanZeroValidator());
		autoBinding_8.bind();
		//
		BeanProperty<CmdLineLauncher, Integer> cmdLineLauncherBeanProperty_9 = BeanProperty.create("repeat");
		AutoBinding<CmdLineLauncher, Integer, JSpinner, Object> autoBinding_9 = Bindings.createAutoBinding(UpdateStrategy.READ_WRITE, cmdLineLauncher, cmdLineLauncherBeanProperty_9, textField_4, jSpinnerBeanProperty);
		autoBinding_9.setValidator(new BiggerThanZeroValidator());
		autoBinding_9.bind();
		//
		BeanProperty<JSpinner, Boolean> jSpinnerBeanProperty_1 = BeanProperty.create("enabled");
		AutoBinding<JCheckBox, Boolean, JSpinner, Boolean> autoBinding_13 = Bindings.createAutoBinding(UpdateStrategy.READ, ckThreads, jCheckBoxBeanProperty, textField_1, jSpinnerBeanProperty_1);
		autoBinding_13.bind();
		//
		AutoBinding<JCheckBox, Boolean, JSpinner, Boolean> autoBinding_16 = Bindings.createAutoBinding(UpdateStrategy.READ, ckRepeat, jCheckBoxBeanProperty, textField_4, jSpinnerBeanProperty_1);
		autoBinding_16.bind();
		//
		ELProperty<JCheckBox, Object> jCheckBoxEvalutionProperty = ELProperty.create("${selected == false}");
		BeanProperty<JComboBox, Boolean> jComboBoxBeanProperty_2 = BeanProperty.create("visible");
		AutoBinding<JCheckBox, Object, JComboBox, Boolean> autoBinding_39 = Bindings.createAutoBinding(UpdateStrategy.READ, ckGeneralPosition, jCheckBoxEvalutionProperty, comboBoxPositionAxis, jComboBoxBeanProperty_2);
		autoBinding_39.bind();
		
	}
}

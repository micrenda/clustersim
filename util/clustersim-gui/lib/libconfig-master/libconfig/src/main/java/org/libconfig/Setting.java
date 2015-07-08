/*******************************************************************************
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS HEADER.
 *
 *
 * Copyright (c) 2013, 2014, Andrey Pleskach (willyborankin@gmail.com). All rights reserved.
 *
 * The libconfig is licensed under the terms of the GPLv2
 * <http://www.gnu.org/licenses/old-licenses/gpl-2.0.html>.
 * There are not special exceptions to the terms and conditions of the GPLv2.
 *
 * This program is free software; you can redistribute it and/or modify it under the terms
 * of the GNU General Public License as published by the Free Software Foundation; version 2
 * of the License.

 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along with this
 * program; if not, write to the Free Software Foundation, Inc., 51 Franklin St, Fifth
 * Floor, Boston, MA 02110-1301  USA
 *
******************************************************************************/
package org.libconfig;

import java.util.ArrayList;
import java.util.List;

public class Setting {

	public static enum Type {
		STRING,
		INTEGER,
		FLOAT,
		BOOLEAN,
		LIST,
		ARRAY,
		GROUP,
		UNKNOWN;
	};
	
	protected String name;
	
	protected Type type;
	
	protected Config config;
	
	protected Setting parent;
	
	protected Object value;
	
	protected Setting(Type type) {
		this(null, type);
	}

	protected Setting(String name, Type type) {
		this.name = name;
		this.type = type;
	}
	
	public String getName() {
		return name;
	}

	@SuppressWarnings("unchecked")
	public <T> T getValue() {
		return (T) value;
	}
	
	public Setting getParent() {
		return parent;
	}
	
	public Type getType() {
		return type;
	}

	public Config getConfig() {
		return config;
	}

	public Setting lookup(String name) {
		Setting found = null;
		if (getName().equals(name)) {
			found = this;
		} else {
			if (type == Type.LIST || type == Type.GROUP) {
				List<Setting> settings = getValue();
				for (Setting setting : settings) {
					found = setting.lookup(name);
					if (found != null) break;
				}
			}
		}
		return found; 
	}

	public <T> T lookupValue(String name) {
		Setting found = lookup(name);
		T value = null;
		if (found != null) value = found.getValue();
		return value;
	}
	
	public String getPath() {
		String path = getName();
		Setting parentCursor = parent;
		while (parentCursor != null) {
			String tmp = path;
			path = parentCursor.getName() + "." + tmp;
			parentCursor = parentCursor.getParent();
		}
		return path;
	}
	
	public <T> Setting addScalar(String name, T value) {
		if (type != Type.GROUP)
			throw new IllegalArgumentException("Such method does not applicable for type " + type);
		applay(name, config.resolveType(value), value);
		return this;
	}
	
	public boolean isSettingExists(String name) {
		Setting setting = lookup(name);
		return setting != null;
	}
	
	public void removeScalar(String name) {
		List<Setting> settings = getValue();
		Setting found = null;
		for (Setting setting : settings) {
			if (setting.getName().equals(name)) {
				found = setting;
				break;
			}
		}
		if (found != null) settings.remove(found);
	}
	
	public <T> Setting addScalar(T value) {
		if (type != Type.LIST)
			throw new IllegalArgumentException("Such method does not applicable for type " + type);
		applay(null, config.resolveType(value), value);
		return this;
	}
	
	public <T> Setting addArray(String name, T[] values) {
		if (type != Type.GROUP)
			throw new IllegalArgumentException("Such method does not applicable for type " + type);
		Setting arraySetting = applaySetting(name, Type.ARRAY);
		arraySetting.value = config.copyArrayValues(values, this);
		return this;
	}
	
	public <T> Setting addArray(T[] values) {
		if (type != Type.LIST)
			throw new IllegalArgumentException("Such method does not applicable for type " + type);
		Setting arraySetting = applaySetting(null, Type.ARRAY);
		arraySetting.value = config.copyArrayValues(values, arraySetting);
		return this;
	}
	
	public Setting addList(String name) {
		if (type != Type.GROUP && type != Type.LIST)
			throw new IllegalArgumentException("Such method does not applicable for type " + type);
		return applaySetting(name, Type.LIST);
	}
	
	public Setting addGroup(String name) {
		if (type != Type.GROUP && type != Type.LIST)
			throw new IllegalArgumentException("Such method does not applicable for type " + type);
		return applaySetting(name, Type.GROUP);
	}
	
	public Setting addGroup() {
		return addGroup(null);
	}
	
	private <T> void applay(String name, Type type, T value) {
		List<Setting> settings = getValue();
		if (settings.contains(name))
			throw new IllegalArgumentException("Duplicate setting name " + name);
		settings.add(config.createSetting(name, type, value, this));
	}
	
	private <T> Setting applaySetting(String name, Type type) {
		List<Setting> settings = getValue();
		if (settings.contains(name))
			throw new IllegalArgumentException("Duplicate setting name " + name);
		Setting setting = config.createSetting(name, type, new ArrayList<>(), this);
		settings.add(setting);
		return setting;
	}
	
	@Override
	public String toString() {
		return "Setting [name=" + name + ", type=" + type + "]";
	}

	@Override
	public int hashCode() {
		final int prime = 31;
		int result = 1;
		result = prime * result + ((name == null) ? 0 : name.hashCode());
		return result;
	}

	@Override
	public boolean equals(Object obj) {
		if (this == obj)
			return true;
		if (obj == null)
			return false;
		if (getClass() != obj.getClass())
			return false;
		Setting other = (Setting) obj;
		if (name == null) {
			if (other.name != null)
				return false;
		} else if (!name.equals(other.name))
			return false;
		return true;
	}
	
}

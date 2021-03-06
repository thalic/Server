/**
 * EQEmulator: Everquest Server Emulator
 * Copyright (C) 2001-2020 EQEmulator Development Team (https://github.com/EQEmu/Server)
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 2 of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY except by those people which sell it, which
 * are required to give you total support for your newly bought product;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 * A PARTICULAR PURPOSE. See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 *
 *
 */

/**
 * This repository was automatically generated and is NOT to be modified directly.
 * Any repository modifications are meant to be made to
 * the repository extending the base. Any modifications to base repositories are to
 * be made by the generator only
 */

#ifndef EQEMU_BASE_NPC_SPELLS_EFFECTS_REPOSITORY_H
#define EQEMU_BASE_NPC_SPELLS_EFFECTS_REPOSITORY_H

#include "../../database.h"
#include "../../string_util.h"

class BaseNpcSpellsEffectsRepository {
public:
	struct NpcSpellsEffects {
		int         id;
		std::string name;
		int         parent_list;
	};

	static std::string PrimaryKey()
	{
		return std::string("id");
	}

	static std::vector<std::string> Columns()
	{
		return {
			"id",
			"name",
			"parent_list",
		};
	}

	static std::string ColumnsRaw()
	{
		return std::string(implode(", ", Columns()));
	}

	static std::string InsertColumnsRaw()
	{
		std::vector<std::string> insert_columns;

		for (auto &column : Columns()) {
			if (column == PrimaryKey()) {
				continue;
			}

			insert_columns.push_back(column);
		}

		return std::string(implode(", ", insert_columns));
	}

	static std::string TableName()
	{
		return std::string("npc_spells_effects");
	}

	static std::string BaseSelect()
	{
		return fmt::format(
			"SELECT {} FROM {}",
			ColumnsRaw(),
			TableName()
		);
	}

	static std::string BaseInsert()
	{
		return fmt::format(
			"INSERT INTO {} ({}) ",
			TableName(),
			InsertColumnsRaw()
		);
	}

	static NpcSpellsEffects NewEntity()
	{
		NpcSpellsEffects entry{};

		entry.id          = 0;
		entry.name        = "";
		entry.parent_list = 0;

		return entry;
	}

	static NpcSpellsEffects GetNpcSpellsEffectsEntry(
		const std::vector<NpcSpellsEffects> &npc_spells_effectss,
		int npc_spells_effects_id
	)
	{
		for (auto &npc_spells_effects : npc_spells_effectss) {
			if (npc_spells_effects.id == npc_spells_effects_id) {
				return npc_spells_effects;
			}
		}

		return NewEntity();
	}

	static NpcSpellsEffects FindOne(
		int npc_spells_effects_id
	)
	{
		auto results = content_db.QueryDatabase(
			fmt::format(
				"{} WHERE id = {} LIMIT 1",
				BaseSelect(),
				npc_spells_effects_id
			)
		);

		auto row = results.begin();
		if (results.RowCount() == 1) {
			NpcSpellsEffects entry{};

			entry.id          = atoi(row[0]);
			entry.name        = row[1] ? row[1] : "";
			entry.parent_list = atoi(row[2]);

			return entry;
		}

		return NewEntity();
	}

	static int DeleteOne(
		int npc_spells_effects_id
	)
	{
		auto results = content_db.QueryDatabase(
			fmt::format(
				"DELETE FROM {} WHERE {} = {}",
				TableName(),
				PrimaryKey(),
				npc_spells_effects_id
			)
		);

		return (results.Success() ? results.RowsAffected() : 0);
	}

	static int UpdateOne(
		NpcSpellsEffects npc_spells_effects_entry
	)
	{
		std::vector<std::string> update_values;

		auto columns = Columns();

		update_values.push_back(columns[1] + " = '" + EscapeString(npc_spells_effects_entry.name) + "'");
		update_values.push_back(columns[2] + " = " + std::to_string(npc_spells_effects_entry.parent_list));

		auto results = content_db.QueryDatabase(
			fmt::format(
				"UPDATE {} SET {} WHERE {} = {}",
				TableName(),
				implode(", ", update_values),
				PrimaryKey(),
				npc_spells_effects_entry.id
			)
		);

		return (results.Success() ? results.RowsAffected() : 0);
	}

	static NpcSpellsEffects InsertOne(
		NpcSpellsEffects npc_spells_effects_entry
	)
	{
		std::vector<std::string> insert_values;

		insert_values.push_back("'" + EscapeString(npc_spells_effects_entry.name) + "'");
		insert_values.push_back(std::to_string(npc_spells_effects_entry.parent_list));

		auto results = content_db.QueryDatabase(
			fmt::format(
				"{} VALUES ({})",
				BaseInsert(),
				implode(",", insert_values)
			)
		);

		if (results.Success()) {
			npc_spells_effects_entry.id = results.LastInsertedID();
			return npc_spells_effects_entry;
		}

		npc_spells_effects_entry = NewEntity();

		return npc_spells_effects_entry;
	}

	static int InsertMany(
		std::vector<NpcSpellsEffects> npc_spells_effects_entries
	)
	{
		std::vector<std::string> insert_chunks;

		for (auto &npc_spells_effects_entry: npc_spells_effects_entries) {
			std::vector<std::string> insert_values;

			insert_values.push_back("'" + EscapeString(npc_spells_effects_entry.name) + "'");
			insert_values.push_back(std::to_string(npc_spells_effects_entry.parent_list));

			insert_chunks.push_back("(" + implode(",", insert_values) + ")");
		}

		std::vector<std::string> insert_values;

		auto results = content_db.QueryDatabase(
			fmt::format(
				"{} VALUES {}",
				BaseInsert(),
				implode(",", insert_chunks)
			)
		);

		return (results.Success() ? results.RowsAffected() : 0);
	}

	static std::vector<NpcSpellsEffects> All()
	{
		std::vector<NpcSpellsEffects> all_entries;

		auto results = content_db.QueryDatabase(
			fmt::format(
				"{}",
				BaseSelect()
			)
		);

		all_entries.reserve(results.RowCount());

		for (auto row = results.begin(); row != results.end(); ++row) {
			NpcSpellsEffects entry{};

			entry.id          = atoi(row[0]);
			entry.name        = row[1] ? row[1] : "";
			entry.parent_list = atoi(row[2]);

			all_entries.push_back(entry);
		}

		return all_entries;
	}

	static std::vector<NpcSpellsEffects> GetWhere(std::string where_filter)
	{
		std::vector<NpcSpellsEffects> all_entries;

		auto results = content_db.QueryDatabase(
			fmt::format(
				"{} WHERE {}",
				BaseSelect(),
				where_filter
			)
		);

		all_entries.reserve(results.RowCount());

		for (auto row = results.begin(); row != results.end(); ++row) {
			NpcSpellsEffects entry{};

			entry.id          = atoi(row[0]);
			entry.name        = row[1] ? row[1] : "";
			entry.parent_list = atoi(row[2]);

			all_entries.push_back(entry);
		}

		return all_entries;
	}

	static int DeleteWhere(std::string where_filter)
	{
		auto results = content_db.QueryDatabase(
			fmt::format(
				"DELETE FROM {} WHERE {}",
				TableName(),
				where_filter
			)
		);

		return (results.Success() ? results.RowsAffected() : 0);
	}

	static int Truncate()
	{
		auto results = content_db.QueryDatabase(
			fmt::format(
				"TRUNCATE TABLE {}",
				TableName()
			)
		);

		return (results.Success() ? results.RowsAffected() : 0);
	}

};

#endif //EQEMU_BASE_NPC_SPELLS_EFFECTS_REPOSITORY_H
